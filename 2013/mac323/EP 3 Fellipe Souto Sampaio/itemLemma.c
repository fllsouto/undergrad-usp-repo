#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "itemWord.h"


/*Transforma a palavra recebida na Key do nó da ARNE*/
Key makeKey(EnglishWord newWord){
	Key aux;
	aux = malloc((int)strlen(newWord.word)*sizeof(char));
	strcpy (aux,newWord.word);
	return aux;
}

/*Faz uma copia da string recebida*/
char *arrangeString(char *myString){
	int x = (int)strlen(myString);
	char *aux = malloc(x*sizeof(char));
	strcpy (aux,myString);
	return aux;
}

/*Compara duas chaves de nós da ARNE*/
int compareKeys (Key A,Key B){
	return strcmp (A,B); 
}