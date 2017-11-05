# Makefile for a basic kernel module

CC=gcc
MODCFLAGS := -Wall -DMODULE -D__KERNEL__ -DLINUX -O2

all:		drink.o


drink.o:	drink.c drink.h /usr/include/linux/version.h
		$(CC) $(MODCFLAGS) -c drink.c
clean:
		rm -f *.o core
