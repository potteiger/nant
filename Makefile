.POSIX:

CFLAGS=-DMODE=0600 -DBUF=32767 -lcurses
nant: nant.c
ant: ant.c

clean:
	rm -f ant nant

