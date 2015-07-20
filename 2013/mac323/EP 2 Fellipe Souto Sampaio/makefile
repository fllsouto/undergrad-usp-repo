# ***************************************************************
#
# Makefile genérico para compilar programas em C
# usando o compilador gcc
#
# ***************************************************************

CFLAGS = -g -I. -Wall -pedantic -ansi
LDFLAGS = -L.
LDLIBS = -lm

RM = /bin/rm -f
CC = gcc

#======================================================================

.c.o:
	$(CC) $(CFLAGS) -c $*.c

.c:
	make $*.o
	$(CC) $(CFLAGS) -o $* $*.o $(LDLIBS)

#======================================================================

clean:
	$(RM) *~ \#~ .\#* *.o core a.out EP2sphere EP2cube

#======================================================================

EP2sphere: client.o Instance.o operation.o Point.S.o
	$(CC) $(CFLAGS) -o EP2sphere Point.S.o operation.o Instance.o client.o $(LDLIBS)

client.o: client.c Instance.h

Instance.o: Instance.c Instance.h operation.h Point.h

operation.o: operation.c operation.h Point.h

Point.S.o : Point.S.c Point.h


EP2cube: client.o Instance.o operation.o Point.C.o
	$(CC) $(CFLAGS) -o EP2cube Point.C.o operation.o Instance.o client.o $(LDLIBS)

client.o: client.c Instance.h

Instance.o: Instance.c Instance.h operation.h Point.h

operation.o: operation.c operation.h Point.h

Point.C.o : Point.C.c Point.h

#A diferenciacão dos dois programas acontecer unica e exclusivamente na hora da ligacão das interfaces Point.C.c e Point.S.c
