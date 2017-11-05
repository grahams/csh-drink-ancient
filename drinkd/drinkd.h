/* 
 *    Drink Server Daemon
 *
 */

/* Various values */
#define BANNER "Drink Server 0.9.2 Ready\n"

#define MACHFILE "/var/local/drinkd/drinkdb"

/* Port number for server */
#define DRINK_PORT 4242
#define NUMSLOTS 7
#define MAXUSERS 100

#define CLIENT_ID 0x01
#define CLIENT_AUTH 0x02

/* Record for each slot */
struct drink_slot {
	char name[16]; /* Name of soda */
	unsigned short cost; /* Cost of a can */
	unsigned int count; /* Number of cans believed to be in machine. */
	unsigned int drops; /* Number of times this slot has been dropped */
};

