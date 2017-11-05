#include <stdio.h> 
#include <stdlib.h> 
#include <errno.h> 
#include <string.h> 
#include <netdb.h> 
#include <sys/types.h> 
#include <netinet/in.h> 
#include <sys/socket.h> 
#include <pwd.h>
#include <fcntl.h>
#include <unistd.h>
    
#define PORT 4242    /* the port client will be connecting to */
#define DRINK_HOST "drink.csh.rit.edu"

#define MAXDATASIZE 100 /* max number of bytes we can get at once */

struct slot {
    int num;
    char name[40];
    int cost;
    int  count;
    struct slot *next;
};

int connect_to_drink();
int login( int sockfd, char *username, char *password );

struct slot *get_machine( int sockfd );
void print_machine( struct slot *machine );
void delete_machine( struct slot *machine );
int drop( int sockfd, int slot );
char *read_line( int sockfd );

int main(int argc, char *argv[])
{
    int sockfd, numbytes;  
    char buf[MAXDATASIZE];
    char username[17];
    char *password;
    int credits;
    int new_credits;
    struct slot *machine;
    char choice;
 
    printf( "CSH Drink Client 0.9.0\n" );
 
    /* Should probably make this get it from the env. */
    printf( "\nEnter Drink Username: " );
    scanf( "%16s", username );
    password = (char*)getpass( "Enter Drink Password: " );
   
    printf( "Connecting to Drink...\n" );

    sockfd = connect_to_drink();

    if ((numbytes=recv(sockfd, buf, MAXDATASIZE, 0)) == -1) {
        perror("recv");
        exit(1);
    }

    buf[numbytes] = '\0';

    printf( "Drink says: %s\n", buf );
    printf( "Logging in... " );
    if( ( credits = login( sockfd, username, password ) ) < 0 ) {
        printf( "ERROR\nInvalid username or password.\n" );
        close( sockfd );
        exit( 0 );
    }
    printf( "done\n" );

    printf( "Downloading machine status..." );
    if( machine = get_machine( sockfd ) )
        printf( " done\n" );
    else {
        printf( "\nCould not retrieve machine state.\n" );
        close( sockfd );
        exit( 1 );
    }

    print_machine( machine );
    
    menu:
    printf( "You have %d credits remaining.\n", credits );
    printf( "\nChoices:\n" );
    printf( "[0-6] Drop Coresponding Drink.\n" );
    printf( "d     Delay a drop\n" );
    printf( "q     Quit\n" );
    printf( "Your selection [0-6dQ]: " );
    scanf( "%2s", &buf );
    choice = buf[0];
    if( ( choice >= '0' ) && ( choice <= '6' ) ) {
        new_credits = drop( sockfd, choice - '0'  );
        if( new_credits < 0 ) {
            printf( "An error occured during drop. You have %d credits remaining.\n", credits );
        }
        else
            printf( "Drop successful. You have %d credits remaining.\n", new_credits );
    }
    else if( ( choice == 'd' ) || ( choice == 'D' ) ) {
        int time_remain;
        int slot;
        printf( "How long do you want to wait (seconds)? " );
        scanf( "%d", &time_remain );
        while( time_remain < 1 ) {
            printf( "Error, please enter a positive value.\n" );
            printf( "How long do you want to wait (seconds)? " );
            scanf( "%d", &time_remain );
        }
        
        printf( "Which slot do you want? " );
        scanf( "%d", &slot );
        while( ( slot < 0 ) || ( slot > 6 ) ) {
            printf( "Invalid slot. Which slot do you want? " );
            scanf( "%d", &slot );
        } 
        printf( "Preparing to drop slot %d in %d seconds... \n", slot, time_remain);
        while( time_remain ) {
            sleep( 1 );
            printf( "%d ", time_remain-- );
            fflush( stdout );
        }
        
        printf( "\nTime's up.\n" );
        new_credits = drop( sockfd, slot );
        if( new_credits < 0 ) {
            printf( "An error occoured during drop. You have %d credits remaining.\n", credits );
        }
        else {
            printf( "Drop successful, you have %d credits remaining.\n", new_credits );
        }
    }
    else if( (choice != 'q') && (choice != 'Q' ) ) {
        printf( "Invalid choice. Please select again.\n" );
        goto menu;
    }
    printf( "Thank you for using CSH drink.\n" );
    delete_machine( machine );  
    close(sockfd);

    return 0;
}

int connect_to_drink() {
    int sockfd;
    struct hostent *he;
    struct sockaddr_in their_addr; /* connector's address information */

    if ((he=gethostbyname(DRINK_HOST)) == NULL) {  /* get the host info */
        herror("gethostbyname");
        exit(1);
    }

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket");
        exit(1);
    }

    their_addr.sin_family = AF_INET;      /* host byte order */
    their_addr.sin_port = htons(PORT);    /* short, network byte order */
    their_addr.sin_addr = *((struct in_addr *)he->h_addr);
    bzero((void*)&(their_addr.sin_zero), 8);     /* zero the rest of the struct */

    if (connect(sockfd, (struct sockaddr *)&their_addr, \
                                          sizeof(struct sockaddr)) == -1) {
        perror("connect");
        exit(1);
    }
    return sockfd;
}

int login( int sockfd, char *user, char *pass ) {
    char buf[MAXDATASIZE];
    int c;

    c = sprintf( buf, "user %s\n", user );
    send( sockfd, buf, c, 0 );
    c = recv( sockfd, buf, MAXDATASIZE, 0 );
    if( ( c < 1 )  || ( strncmp( buf, "OK ", 2 ) ) ) {
        return -1;
    }
 
    c = sprintf( buf, "pass %s\n", pass );
    send( sockfd, buf, c, 0 );
    memset( buf, 0, MAXDATASIZE );
    c = recv( sockfd, buf, MAXDATASIZE, 0 );
    if( ( c < 1 ) || ( strncmp( buf, "OK ", 3 ) ) ) {
        return -1;
    }
    sscanf( buf, "OK Credits: %d", &c ); 
    return c;
}

struct slot* get_machine( int sockfd ) {
    char *buf;
    char eod = 0;
    struct slot *root = NULL;
    struct slot *tail = NULL;
    send( sockfd, "stat\n", 5, 0 );
    buf = read_line( sockfd );
    while( !eod ) {
        int pos = 0;
        eod = strncmp( "OK ", buf, 3 ) == 0;
        if( !eod ) {
            struct slot *new_slot = malloc( sizeof( struct slot ) );
            sscanf( buf, "%d %s %d %d %*d", &new_slot->num, &new_slot->name, 
                 &new_slot->cost, &new_slot->count );
            new_slot->next = NULL;

            if( !root ) {
                root = new_slot;
                tail = new_slot;
            }
            else {
                tail->next = new_slot;
                tail = tail->next;
            }
            buf = read_line( sockfd );
        }
   }

   return root;
}

void print_machine( struct slot *machine ) {
    struct slot *current = machine;
    printf( "SLOT  DRINK          COST    STATUS\n" );
    printf( "-----------------------------------\n" );
    while( current ) {
        printf( " %d    %-15s %d    %s\n", current->num,  current->name, 
            current->cost, (current->count)?"AVAILABLE":"**EMPTY**" );
        current = current->next;
    }
    printf( "----------------------------------\n\n" );
}

void delete_machine( struct slot *machine ) {
    struct slot *current = machine;
    struct slot *next;
    while( current ) {
       next = current->next;
       free( current );
       current = next;
    }
}
  
int drop( int sockfd, int slot ) {
    char buf[MAXDATASIZE];
    int c;
    c = sprintf( buf, "drop %d\n", slot );
    send( sockfd, buf, c, 0 );
    c = recv( sockfd, buf, MAXDATASIZE, 0 );
    if( ( c < 1 ) || strncmp( buf, "OK ", 3 ) ) {
        return -1;
    }
    sscanf( buf, "OK Credits remaining: %d", &c );
    return c;
}

char *read_line( int sockfd ) {
    static char line[MAXDATASIZE];
    char *pbuf;
    int len;

    pbuf = line;
    memset( line, 0, MAXDATASIZE );
    len = recv( sockfd, pbuf, 1, 0 );
    while( *( pbuf ) != '\0' ) {
        pbuf++;
        len = recv( sockfd, pbuf, 1, 0 );
    }
    return line;
}
     
