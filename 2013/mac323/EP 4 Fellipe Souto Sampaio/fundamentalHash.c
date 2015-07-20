#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fundamentalHash.h"
/*chaves no intervalo [0,M-1]*/
int hashFunction(Key v, int M){
	
	int h = 0;
	int a = 127;
	
	for(; *v != '\0'; v++)
		h = (a*h +*v)% M;
	
	return h;
}

char *arrangeString(char *myString){
	int x = (int)strlen(myString);
	char *aux = malloc(x*sizeof(char));
	strcpy (aux,myString);
	return aux;

}
int compareKeys (Key A,Key B){
	/*printf ("word = %s  X word2 = %s, result : %d\n",A,B,(int)strcmp (A,B));*/
	return strcmp (A,B); 
}