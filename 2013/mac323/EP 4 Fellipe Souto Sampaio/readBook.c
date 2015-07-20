#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "readBook.h"
#include "interface.h"
#define endOfSentence '\0' /*as strings são marcadas com o caracter EndOfText*/
#define maxChar 1024
#define TRUE 1
#define FALSE 0
#define out_of_mem(x) {  printf("Memoria insuficiente, programa abortado!\n"); \
                         exit(x); \
                      }
#define jumpLine '|'


typedef struct {
	char *sentence;
	int token;
	int sentenceNumber;
	
	
}bookSentence;

typedef struct {
    long begin;
    long middle;
    long end;
    
}bookPointer;

static char *bookName;
int maxLen = maxChar;
int totalSentence;
bookSentence *newBook;
bookPointer *newPointer;
/*limpa o lixo da memória*/
static void cleanTrash(char *vector,int l){
	
	int x = 0;
	
	for (;x < l;x++)
		vector[x] = ' '; 
	
}
/*Extrai a setenća de uma senteća anotada*/
static bookSentence extractSentece(char *newLine){ /*remover o que não é necessário*/
	bookSentence newSentence;
	char *ptr = strstr(newLine,"[Text=");
	long j = ptr - newLine;
	long k;
	int x = 0;
	
	char *sentence = malloc (j*sizeof(char));
	if (!sentence)
		out_of_mem(-1);
	
	for (; x< j; x++)
		sentence[x] = newLine[x];
	
	sentence[j-1] = '\0';
	
	ptr = strchr(sentence,':');
	j = ptr - sentence;
	k = (long)strlen(sentence);
	newSentence.sentence = malloc((k-j)*sizeof(char));
	if (!newSentence.sentence)
		out_of_mem(-1);
	
	sscanf(sentence,"Sentence #%d (%d tokens): %[^32]s",&newSentence.sentenceNumber,&newSentence.token,newSentence.sentence);
	free(sentence);
	return newSentence;

}
/*Imprime sentenćas anotadas*/
void printAnnotated(int x){

    long i = newPointer[x].begin;
    long f = newPointer[x].end;
    long k = 0;
    char c;
    FILE *entrada;
    
    if (x > totalSentence)
        return;
    
    entrada = fopen(bookName,"r");
    fseek(entrada, i, SEEK_SET);
    
    for (k = i; k < f; k++){
        c = fgetc(entrada);
        printf ("%c",c);
    }
    
}


/*Imprime Sentenćas*/
void printSentence(int k,char opt){
	
	int x = 0;
	if (opt == 'v')
		printf("Sentence Number #%d Tokens : %d",newBook[k].sentenceNumber,newBook[k].token);
	
	for (; x < (int)strlen(newBook[k].sentence); x++){
		if (newBook[k].sentence[x] == jumpLine)
			printf ("\n");
		else
			printf ("%c",newBook[k].sentence[x]);
	}
	printf ("\n\n--------------------------------------------------------------------------\n\n");
}


/*Faz a extraćão dos lemas e palavras de uma sentenća*/
static void extractLema(char *newLine, int sentenceNumber){
	
	long length = 	length = (long)strlen(newLine) - (long)(strchr(newLine,'[' ) - newLine) + 1;
	long aux = (long)(strchr(newLine,'[' ) - newLine);
	long i = 0;
	int fl1 = FALSE;
	int fl2 = FALSE;
	char *lemmatization = malloc(length*sizeof(char));
	char *auxpointer;
	char text[256]; /*Estou assumindo que o tamanho máximo que uma palavra/Lemma possa ter é de 256 caracteres*/
	char lemma[256];
		
	cleanTrash(lemmatization,length);
	
	for (;i<length;i++)
		lemmatization[i] = newLine[aux+i];
	
	auxpointer = strtok (lemmatization,"] [");
	while (auxpointer != NULL){
				
		if(sscanf(auxpointer,"Text=%s",text))
			fl1 = TRUE;
		if(sscanf(auxpointer,"Lemma=%s",lemma))
			fl2 = TRUE;
		if (fl1 && fl2){
			STinsertion(text,lemma,sentenceNumber);
			fl1 = fl2 = FALSE;
		}
		
		auxpointer = strtok (NULL,"] [");
	}
	
}


/*Ajusta o tamanho do array de caracteres*/
static char* resizeVector (char *aux,int x){
	char *tempvec;
	int l = 0;

	maxLen *= 2;
	tempvec = malloc(maxLen*sizeof(char));
	
	if (!tempvec)
		out_of_mem(-1);
	cleanTrash(tempvec,maxLen);
	for (;l<= x; l++)
		tempvec[l] = aux[l]; 
	
	free(aux);
	return tempvec;
	
}

/*Leitura do arquivo de texto separando-o em setenćas, lemas, palavras e sentenćas anotadas*/
void STstartReadBook(char *bkName){
	char character;
	long ioMani = 0;
	long bufferPos = 0;
	int kIndx = 0;
	int x = 0;
	int newNode = 0;
	int l = 0;
	char *aux;
	char *vec2;
	
	FILE *entrada;
	bookSentence *tempNewBook;
	bookPointer *temp;
	
	newPointer = malloc(sizeof(bookPointer));
	newBook = malloc(sizeof(bookSentence));
	
	
	if (!newBook)
		out_of_mem(-1);
	
	aux = malloc(maxLen*sizeof(char));
	if (!aux)
		out_of_mem(-1);
	
	cleanTrash (aux,maxLen);
	
	bookName = malloc ((int)strlen(bkName)*sizeof(char));
	strcpy(bookName,bkName);
	entrada = fopen(bookName,"r");
	
	newPointer[0].begin = ftell(entrada);
	while ((character = fgetc(entrada)) != EOF){
		if(character == '\n')	
			character = jumpLine;
	
		aux[x] = character;
		if (2*x > maxLen){
			aux = resizeVector(aux, x);
		}
		
		if (strstr(aux,"] |Sentence") != NULL){
			char *vec;
			int l = 0;
			ioMani = ftell(entrada) - (long)strlen("Sentence");
			kIndx = x - 8;
			vec = malloc(kIndx*sizeof(char));
			cleanTrash (vec,kIndx);
		
			for (;l< kIndx-1; l++){
				vec[l] = aux[l];
			}
			
			
			vec[kIndx-1] = endOfSentence;
			fseek(entrada, ioMani, SEEK_SET);
			maxLen = maxChar;
			x = 0;
			
			newBook[newNode] = extractSentece(vec);
			extractLema(vec, newBook[newNode].sentenceNumber);
			
			newPointer[newNode].end = ioMani-1;
			
			newNode++;
			temp = (bookPointer*)realloc(newPointer,(newNode+1)*sizeof(bookPointer));
			
			if (temp == NULL){
				out_of_mem(-1);	
			}
			newPointer = temp;
			newPointer[newNode].begin = ioMani;
			
			
			tempNewBook = (bookSentence*)realloc(newBook,(newNode+1)*sizeof(bookSentence));
				
			if (tempNewBook == NULL){
				out_of_mem(-1);	
			}
			else
				newBook = tempNewBook;
			
			
			
			free(aux);

			aux = malloc(maxLen*sizeof(char));
			cleanTrash (aux,maxLen);
			continue;
		}
		bufferPos = ftell(entrada);
		x++;
	}
	
	kIndx = x;
	vec2 = malloc(kIndx*sizeof(char));
	cleanTrash (vec2,kIndx);
		
	for (;l< kIndx-1; l++){
		vec2[l] = aux[l];
	}
	vec2[kIndx-1] = endOfSentence;
	newBook[newNode] = extractSentece(vec2);
	extractLema(vec2, newBook[newNode].sentenceNumber);
	
 
			
	newNode++;
	
	temp = (bookPointer*)realloc(newPointer,(newNode+1)*sizeof(bookPointer));
	if (temp == NULL){
		out_of_mem(-1);	
	}
	newPointer = temp;
	newPointer[newNode-1].begin = newPointer[newNode-2].end +1;
	newPointer[newNode-1].end = bufferPos;
	
			
	tempNewBook = (bookSentence*)realloc(newBook,(newNode+1)*sizeof(bookSentence));
				
	if (tempNewBook == NULL){
		out_of_mem(-1);	
	}
	else
		newBook = tempNewBook;
	
			
	fclose(entrada);
	totalSentence = newNode;
	return;
}


