#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <mysql/mysql.h>
#include "sql.h"

int sql_auth( char *username, char *password, MYSQL *server ) {
    char query[250];
    int numrec;
    int retval;
    char salt[3];
    int is_auth;

    MYSQL_RES *results;
    MYSQL_ROW row;

    sprintf( query, "SELECT password FROM drinkusers WHERE username=\'%s\'", username );

    retval = mysql_real_query( server, query, strlen( query ) );
    if( retval ) {
        return -1;
    }

    results = mysql_store_result( server );
    if( results == NULL ) {
        return -1;
    }

    numrec = mysql_num_rows( results );
    if( numrec != 1 ) {
        return 0;
    }
    row = mysql_fetch_row( results );
    
    strncpy( salt, row[0], 2 );
    salt[2] = 0;
    is_auth =  strcmp( row[0], (char*)crypt( password, salt ) ) == 0; 
    mysql_free_result( results );
    return is_auth;
}

int query_credits( char *username, MYSQL *server ) {
    char query[250];
    int numrec;
    int retval;
    int credits;
    MYSQL_RES *results;
    MYSQL_ROW row;
    sprintf( query, "SELECT credits FROM drinkusers WHERE username=\'%s\'", username );

    retval = mysql_real_query( server, query, strlen( query ) );
    if( retval ) {
        return -1;
    }
 
    results = mysql_store_result( server );
    if( results == NULL ) {
        return -1;
    }

    numrec = mysql_num_rows( results );
    if( numrec != 1 ) {
        return -1;
    }
    row = mysql_fetch_row( results );
    credits = atol( row[0] );

    mysql_free_result( results );

    return credits;
}

int deduct_credits( char *username, int credits, MYSQL *server ) {
    char query[200];

    sprintf( query, "UPDATE drinkusers SET credits=credits-%d WHERE username=\'%s\'", credits, username );
    return mysql_real_query( server, query, strlen( query ) );
}

int sql_lock( MYSQL *server ) {
    char query[] = "LOCK TABLES drinkusers WRITE"; 
    return mysql_real_query( server, query, strlen( query ) );
}

int sql_unlock( MYSQL *server ) {
    char query[] = "UNLOCK TABLES";
    return mysql_real_query( server, query, strlen( query ) );
}

