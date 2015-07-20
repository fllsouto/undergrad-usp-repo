# ***************************************************************
#
#
# 
#
# ***************************************************************

CFLAGS = -g -I. -Wall -pedantic -ansi
LDFLAGS = -L.
LDLIBS = -lm
objects = client.o interface.o readBook.o lemmaTree.o wordTree.o itemWord.o 

RM = /bin/rm -f
CC = gcc

clean:
	$(RM) *~ \#~ .\#* $(objects) core a.out 

cleanexec:
	$(RM) ep3

#======================================================================

ep3: $(objects)
	$(CC) $(CFLAGS) -o ep3 $(objects) $(LDLIBS)


client.o: interface.h readBook.h

readBook.o: readBook.h interface.h

interface.o: lemmaTree.h wordTree.h readBook.h

lemmaTree.o: lemmaTree.h itemLemma.h

wordTree.o: wordTree.h itemWord.h

itemWord.o: itemWord.h

itemTree.o: itemTree.h
