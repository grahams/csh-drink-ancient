int query_credits( char *username, MYSQL *server );
int deduct_credits( char *username, int credits, MYSQL *server );

int sql_auth( char *username, char *password, MYSQL *server );

int sql_lock( MYSQL *server );
int sql_unlock( MYSQL *server );
