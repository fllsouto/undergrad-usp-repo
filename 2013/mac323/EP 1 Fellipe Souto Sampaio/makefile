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
	$(RM) *~ \#~ .\#* *.o core a.out

#======================================================================

EP1: client.o Instance.o creation.o operation.o
	$(CC) $(CFLAGS) -o EP1 operation.o creation.o Instance.o client.o $(LDLIBS)

client.o: client.c Instance.h

Instance.o: Instance.c Instance.h Graph.h creation.h operation.h

creation.o: creation.c creation.h Graph.h

operation.o: operation.c operation.h Graph.h


#Para executar a compilação, no terminal do linux estando na pasta com os arquivos
#do ep digite : make EP1
#
