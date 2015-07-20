#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "wordProb.h"
#include "wordEnc.h"
#include "lemmaEnc.h"
#include "lemmaProb.h"
#include "interface.h"
#include "handlingWord.h"
#include "handlingLemma.h"
#include "readBook.h"

void STstart(){
	
	STinitWordHashing();
	STinitLemmaHashing();
}

static char* lowerCaseLetter (char *word){
	int len = (int)strlen(word);
	int x = 0;
	for(;x< len; x++)
		word[x] = tolower(word[x]);
	
	return word;
}

void STinsertion(char *word,char *lemma, int position){	
	SThandlingWord(lowerCaseLetter(word),lowerCaseLetter(lemma),position);
	SThandlingLemma(lowerCaseLetter(lemma),lowerCaseLetter(word),position);

}


void STseekWord(char *word,char op){
	
	int *aux = STinjectedWord (lowerCaseLetter(word));
	int x = 1;

	printf ("Word : %s\n\n",word);
	if(aux != NULL){
		for (; x < aux[0]; x++){
			/*if(aux[x] != aux[x-1]){*/
				if (op == 'V'){
				    printf ("\n\n---------------------------------------------------------\n\n");
					printAnnotated(aux[x]-1);
				}
				else
					printSentence(aux[x] -1,op);

		}
	}
	else{
		printf ("A palavra nao esta disponivel!\n");
	}
	printf ("\n");
	
}

void STseekLemma(char *lemma,char op){
	int x= 0;
	int k = STinjectedLemmaLocal (lowerCaseLetter(lemma)	);
	char** result = STinjectedLemma(lowerCaseLetter(lemma));
	
	printf (">> Lemma : %s\n\n",lemma);
	if (result != NULL){
		for(; x < k; x++){
			STseekWord(result[x],op);
		}
	}
	else{
		printf ("O lema : %s nao foi inserida\n",lemma);
	}


}


void clear_newlines(){ 
    int c;
    do
    {
        c = getchar();
    } while (c != '\n' && c != EOF);
}
