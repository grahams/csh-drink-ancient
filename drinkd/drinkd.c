/* Drink Daemon */

#include "drinkd.h"
#include "secrets.h"
#include "socket.h"

#include <errno.h>       /* obligatory includes */
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <mysql/mysql.h>
#include "sql.h"


/* Array of slot structures */
struct drink_slot machine[NUMSLOTS];

/* Load the machine state from disk */
void read_machine();
void write_machine();

/* Send status to the socket. */
void stat( int s );
int drop( int slot );
void message( int s, char *msg );

int authenticate( char *username, char *passwd );

void fireman(int);
void reload(int);
void clean_shutdown(int);
void do_something(int);

int zdaemon( void );
int is_empty( int slot );
int main()
{ 
  int s, t;
  
  if( zdaemon() == -1 ) {
    _exit( 1 );
  }
  if ((s= establish(DRINK_PORT)) < 0) {  /* plug in the phone */
    perror("establish");
    exit(1);
  }

  reload( 0 );

  signal(SIGCHLD, fireman);           /* this eliminates zombies */
  signal(SIGHUP, reload );            /* kill -HUP to reload db files. */
  signal(SIGTERM, clean_shutdown );         /* Gracefully close out. */

  for (;;) {                          /* loop for phone calls */
    if ((t= get_connection(s)) < 0) { /* get a connection */
      if (errno == EINTR)             /* EINTR might happen on accept(), */
        continue;                     /* try again */
      perror("accept");               /* bad */
      exit(1);
    }
    switch(fork()) {                  /* try to handle connection */
    case -1 :                         /* bad news.  scream and die */
      perror("fork");
      close(s);
      close(t);
      exit(1);
    case 0 :                          /* we're the child, do something */
      close(s);
      do_something(t);
      exit(0);
    default :                         /* we're the parent so look for */
      close(t);                       /* another connection */
      continue;
    }
  }
}

/* as children die we should get catch their returns or else we get
 * zombies, A Bad Thing.  fireman() catches falling children.
 */
void fireman(int sig)
{
  while (waitpid(-1, NULL, WNOHANG) > 0)
    ;
}

void reload(int sig)
{ 
  read_machine();
}

void clean_shutdown(int sig)
{
  write_machine();
}

/* this is the function that plays with the socket.  it will be called
 * after getting a connection.
 */
void do_something( int s ) {
  char banner[] = BANNER;
  char buffer[256];
  char status = 0;
  char username[16];
  int i;
  
  MYSQL *server;
  server = mysql_init( NULL );

  server = mysql_real_connect( server, SQL_HOST, SQL_USER, SQL_PASS, SQL_DB,  0, NULL, 0 );

  reload( 0 );
  send( s, banner, strlen( banner ) + 1, 0 );

  memset( buffer, 0, 255 );
  while( ( i = recv( s, buffer, 255, 0 ) ) > 0 ) {
    char tmp[6];
    char cmd[6];

    sscanf( buffer, "%5s", tmp );

    for( i = 0; i < 4; i++ ) {
      cmd[i] = tolower( tmp[i] );
    }
    cmd[4] = 0;

    if( strcmp( cmd, "stat" ) == 0 ) {
      stat( s );
    }
    else if( strcmp( cmd, "user" ) == 0 ) {
        if( sscanf( buffer + 5, "%15s", username ) == EOF ) {
	  message( s, "ERR Username required.\n" );
	  status = 0;
	}
	else {
	  status = CLIENT_ID;
	  message( s, "OK Password required.\n" );
	}
    }

    else if( strcmp( cmd, "pass" ) == 0 ) {
      char pwd[16];
      if( status & CLIENT_ID ) {
	if( status & CLIENT_AUTH ) {
	  message( s, "ERR You're already authenticated!\n" );
	}
	else {
          int ret;
	  sscanf( buffer + 5, "%15s", pwd );
	  ret = sql_auth( username, pwd, server ); 
	  if( ret < 0 ) {
            message( s, "ERR An error occoured during authentication.\n" );
            status = 0;
          }
          else if( ret ) {
            char msg[30];
            
	    sprintf( msg, "OK Credits: %d\n", query_credits( username, server ) );
	    message( s, msg );
	    status |= CLIENT_AUTH;
	  }
	  else {
	    message( s, "ERR Invalid username or password.\n" );
	    status = 0;
	  }
	}
      }
      else {
	message( s, "ERR You need to identify yourself first.\n" );
      }
    }
    else if( strcmp( cmd, "drop" ) == 0 ) {
      if( status & CLIENT_AUTH ) {
	int slot;
	if( sscanf( buffer + 5, "%d", &slot ) == EOF ) {
	  message( s, "ERR You must specify slot\n" );
	}
	else if( ( slot < NUMSLOTS ) && ( slot >= 0 ) ) {
	  if( !is_empty(slot) ) {
            sql_lock( server );
            if( machine[slot].cost <= query_credits( username, server ) ) {
	      char msg[60];
	      if( drop( slot ) != -1 ) {
                  deduct_credits( username, machine[slot].cost, server );
	          sprintf( msg, "OK Credits remaining: %d\n", query_credits( username, server ) );
                  printf( "Slot %d (%s) dropped by %s\n", slot, 
                           machine[slot].name, username );
	      }
    	      else {
                  sprintf( msg, "ERR Machine Failure on drop. Credits remaining: %d\n", query_credits( username, server ) );
              }
		  message( s, msg );
	    }
	    else {
	      message( s, "ERR Insuficient Credits.\n" );
	    }
            sql_unlock( server );
	  }
	  else {
	    message( s, "ERR Slot appears to be empty\n" );
	  }
	}
	else {
	  message( s, "ERR Invalid slot number.\n" );
	}
      }
      else {
	message( s, "ERR You need to login first.\n" );
      }
    }
    else if( strcmp( cmd, "quit" ) == 0 ) {
      message( s, "OK Goodbye\n" );
      break;
    }
    else {
      message( s, "ERR Invalid command\n" );
    }
    memset( buffer, 0, 255 );
  }
  close( s );
}

void stat(int s)
{
        char temp[40];
	int i;
	int c;
        int drink;
        char mask;
        drink = open( "/dev/drink", O_RDONLY );
        read( drink, &mask, 1 );
        close( drink );

        read_machine();
	for( i = 0; i < NUMSLOTS; i++ ) {
	  c = sprintf( temp,  "%d %s %d %d %d\n", i, 
                      machine[i].name, machine[i].cost,
		      is_empty( i )?0:machine[i].count, machine[i].drops );
	  send( s, temp, c+1, 0 );
	}
	c = sprintf( temp, "OK %d Slots retrieved\n", NUMSLOTS );
        send( s, temp, c+1, 0 );
}

void read_machine() {
	FILE *drinkdb;
	int i;

	if( ( drinkdb = fopen( MACHFILE, "r" ) ) == NULL ) {
		perror( "read_machine" );
	}
	
	for( i = 0; i < NUMSLOTS; i++ ) {
		fscanf( drinkdb, "%s %d %d %d", &machine[i].name,
		                             &machine[i].cost,
					     &machine[i].count,
					     &machine[i].drops );
	} 
	fclose( drinkdb );
}

void write_machine() {
  FILE *drinkdb;
  int i;
  if( ( drinkdb = fopen( MACHFILE, "w" ) ) != NULL ) {
    for( i = 0; i < NUMSLOTS; i++ ) {
      fprintf( drinkdb, "%s %d %d %d\n", machine[i].name,
	       machine[i].cost, machine[i].count, machine[i].drops );
    }
  }
  fclose( drinkdb );
}

void message( int s, char *msg ) {
  send( s, msg, strlen( msg ), 0 );
}

int drop( int slot ) {
  int drink;
  int ret;

  drink = open( "/dev/drink", O_WRONLY );

  ret = write( drink, &slot, 1 );
  close( drink ); 
  
  if( ret != -1 ) {
       machine[slot].count--;
       machine[slot].drops++;
  }
  write_machine();
  return ret;
}


/* daemon() -- detach process from user and disappear into the background
 * returns -1 on failure, but you can't do much except exit in that case
 * since we may already have forked. This is based on the BSD version,
 * so the caller is responsible for things like the umask, etc.
 */

/* believed to work on all Posix systems */

int zdaemon( void )
{
    switch (fork())
    {
        case 0:  break;
        case -1: return -1;
        default: _exit(0);          /* exit the original process */
    }

    if (setsid() < 0)               /* shoudn't fail */
      return -1;

    /* dyke out this switch if you want to acquire a control tty in */
    /* the future -- not normally advisable for daemons */

    switch (fork())
    {
        case 0:  break;
        case -1: return -1;
        default: _exit(0);
    }

    return 0;
}

int is_empty( int slot ) {
    int machine;
    char mask;

    machine = open( "/dev/drink", O_RDONLY );
    read( machine, &mask, 1 );
    close( machine );

    return ( mask & ( 1 << slot ) );
}





