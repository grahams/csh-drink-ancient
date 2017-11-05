CC=gcc
CFLAGS:= -O2 -Wall -L/usr/local/lib/mysql
LIBS=-lcrypt -lmysqlclient
OBJS=drinkd.o sql.o socket.o
EXECS=drinkd

all: drinkd

drinkd: $(OBJS)
	$(CC) $(CFLAGS) -o drinkd $(OBJS) $(LIBS)

drinkd.o: drinkd.c
	$(CC) $(CFLAGS) -c drinkd.c
sql.o: sql.c
	$(CC) $(CFLAGS) -c sql.c
socket.o: socket.c
	$(CC) $(CFLAGS) -c socket.c

clean:
	rm -f $(OBJS) $(EXECS)
