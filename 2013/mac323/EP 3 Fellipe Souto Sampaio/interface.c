#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "readBook.h"
#include "lemmaTree.h"
#include "wordTree.h"
#define FALSE 0
#define TRUE 1

/*Inicializa as duas árvores*/
void STstart(){
	STinitWordTree();
	STinitLemmaTree();
}
/*Verifica se a palavra possui algum caracter maiusculo e converte tudo para minúsculo*/
static char* lowerCaseLetter (char *word){
	int len = (int)strlen(word);
	int x = 0;
	for(;x< len; x++)
		word[x] = tolower(word[x]);
	
	return word;
}

/*funćão de inserćão de palavras e lemas nas árvores*/
void STinsertion(char *word,char *lemma, int positon){
	word = lowerCaseLetter(word);
	lemma = lowerCaseLetter(lemma);
	STappendWordTree(word,lemma,positon);
	STappendLemmaTree(word,lemma,positon);	
}

/*Funcão de busca de uma palavra na árvore*/
void STsearchWord(char *word,char op){
	int *aux = STsearchWordText(lowerCaseLetter(word));
	int x;

	printf ("Word : %s\n\n",word);
	if(aux != NULL){
		for (x = 1; x < aux[0]; x++){
			if(aux[x] != aux[x-1]){
				if (op == 'V'){
					printAnnotated(aux[x]-1);
				}
				else
					printSentence(aux[x] -1,op);
			}
		}
	}
	else{
		printf ("A palavra nao esta disponivel!\n");
	}
	printf ("\n");
}
/*Funćão de busca de um lemma em uma árvore*/
void STsearchLemma(char *lemma,char opt){
	int x= 0;
	char** result = STsearchLemmaText(lowerCaseLetter(lemma));

	if (result != NULL){
		while(result[x] != NULL){
			STsearchWord(result[x],opt);
			x++;
		}
	}
	else{
		printf ("O lema : %s nao foi inserida\n",lemma);
	}
}

/*limpa o return digitado*/
void clear_newlines(){ 
    int c;
    do
    {
        c = getchar();
    } while (c != '\n' && c != EOF);
}
/*Imprime a sentenća anotada*/
void STannotated(char *word){
	STsearchWord(word,'V');
}

