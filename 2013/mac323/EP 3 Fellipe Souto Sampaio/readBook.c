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

int maxLen = maxChar;
bookSentence *newBook;
char **annotatedSentence;
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
	int len = (int)strlen (annotatedSentence[x]);
	int k = 0;
	
	for (; k < len; k++){
		if (annotatedSentence[x][k] == jumpLine)
			printf ("\n");
		else
			printf ("%c",annotatedSentence[x][k]);
	}
	
	printf ("\n\n--------------------------------------------------------------------------\n\n");
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
			/*printf ("%s : %s \n",text,lemma);*/
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
void STstartReadBook(char *bookName){
	char character;
	char **tempAnnotated;
	long ioMani = 0;
	int kIndx = 0;
	int x = 0;
	int newNode = 0;
	char *aux;
	char *vec2;
	int l = 0;
	FILE *entrada;
	bookSentence *tempNewBook;
	newBook = malloc(sizeof(bookSentence));
	annotatedSentence  = malloc(sizeof(char*));
	
	if (!newBook)
		out_of_mem(-1);
	
	aux = malloc(maxLen*sizeof(char));
	if (!aux)
		out_of_mem(-1);
	
	cleanTrash (aux,maxLen);
	
	entrada = fopen(bookName,"r");
	
	
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
			
			annotatedSentence[newNode] = malloc(((int)strlen(vec)+1)*sizeof(char));
			
			strcpy(annotatedSentence[newNode],vec);
			newNode++;
			tempAnnotated = (char**)realloc(annotatedSentence,(newNode+1)*sizeof(char*));
			
			if (tempAnnotated == NULL){
				out_of_mem(-1);	
			}
			annotatedSentence = tempAnnotated;
			
			
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
			
	annotatedSentence[newNode] = malloc(((int)strlen(vec2)+1)*sizeof(char));
			
	strcpy(annotatedSentence[newNode],vec2);
	newNode++;
	tempAnnotated = (char**)realloc(annotatedSentence,(newNode+1)*sizeof(char*));
			
	if (tempAnnotated == NULL){
		out_of_mem(-1);	
	}
	annotatedSentence = tempAnnotated;
			
			
	tempNewBook = (bookSentence*)realloc(newBook,(newNode+1)*sizeof(bookSentence));
				
	if (tempNewBook == NULL){
		out_of_mem(-1);	
	}
	else
		newBook = tempNewBook;
	
			
	fclose(entrada);
	return;
}

