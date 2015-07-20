#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fundamentalHash.h"
#include "lemmaDefs.h"
#include "lemmaProb.h"
#define TRUE 1
#define FALSE 0
typedef struct STnode *link;

struct STnode{ 
	EnglishLemma englishWord; 
};

static link *heads, z, *rebuild;
static int N, M, primeN;
static float load_Factor;
static int primeN;


static link NEW(EnglishLemma newWord)
{
    link x = malloc(sizeof *x);
    x->englishWord = newWord;    
	return x;
}

static EnglishLemma STinitCell(){
	EnglishLemma newWord;
	newWord.word = NULL;
	newWord.sentenceArray = NULL;
	newWord.sentenceLocal = NULL;
	return newWord;
}

void STinitLemmaHashing(){ 
	int i;
	EnglishLemma newWord;
	N = 0;
	primeN = 0;
	M = primetable[primeN];
	newWord = STinitCell();

   	heads = malloc(M*sizeof(link));
   	z = NEW(newWord);
	for (i = 0; i < M; i++) 
		heads[i] = z; 
}

static void rebuildHash(int primeFactor){
	int i;

   	rebuild = malloc(primeFactor*sizeof(link));
	
	for (i = 0; i < primeFactor; i++) 
		rebuild[i] = z;
	
	for (i = 0; i < M; i++) {
		if (heads[i] != z){
			int k = hashFunction(heads[i]->englishWord.word, primeFactor);			

			while (rebuild[k] != z)
				k = (k+1)% primeFactor;
				
			rebuild[k] = heads[i];
		}
	}
		
	free (heads);
	heads = rebuild;
	M = primeFactor;
	load_Factor = (1.0*N)/M;

}

static Key hashKey(EnglishLemma newWord){
	Key aux;
	aux = malloc((int)strlen(newWord.word)*sizeof(char));
	strcpy (aux,newWord.word);
	return aux;
}

static void STinsert(EnglishLemma englishWord){
	/*a cada inserćão N é incrementado*/
	int i = hashFunction(hashKey(englishWord), M);

	while (heads[i] != z){
		i = (i+1)% M;
	}
	heads[i] = NEW(englishWord); 
	N++;
	load_Factor = (1.0*N)/M;
	
	if (load_Factor >= 0.5){

		primeN++;
		rebuildHash(primetable[primeN]);
	}
}

void STpreInsertLemma(char *lemma,char *word, int sentenceNumber){
	
	char **senteceList = malloc(sizeof(char*));
	EnglishLemma newWord;

	newWord = STinitCell();
	newWord.word = arrangeString(lemma);
	senteceList[0] = arrangeString(word);
	newWord.sentenceArray = (char**)realloc(senteceList,sizeof(char*));
	newWord.sentenceLocal = malloc(sizeof(int));
	newWord.sentenceLocal[0] = 1; /*quantidade de palavras indexadas pelo mesmo lema*/
	STinsert(newWord);
}


static int searchR(int hashVal, Key v){ 
    int i = hashVal;
	
	while(heads[i] != z){
		if (compareKeys(heads[i]->englishWord.word, v) == 0)
			return 1;
		
		i = (i+1)%M; 
	}
	return 0;
}
/*diferenca entre maiusculas e minusculas*/
int STsearchLemma(char *searchedWord){ 
	int i = hashFunction(searchedWord, M);
	int temp;

	temp = searchR(i,searchedWord);
	if (temp == 0){

		return  0;
	}
	else{

		return 1;
	}
}

static void fixSentenceLemmas(link h, char *lemma,char *word){

	char **k;
	int t;
	int f = 0;
	for (;f < h->englishWord.sentenceLocal[0]; f++){
		if (strcmp (h->englishWord.sentenceArray[f],word) == 0)
			return;
	}
	h->englishWord.sentenceLocal[0]++ ; 
	t = h->englishWord.sentenceLocal[0];
	k = (char **)realloc(h->englishWord.sentenceArray,t*sizeof(char *));
	k[t-1] = arrangeString(word);
	h->englishWord.sentenceArray = k;

}

void STrepetedLemmaInsertion(char *lemma,char *word){
	
	int i = hashFunction(lemma, M);	
	
	while(heads[i] != z){
		if (compareKeys(heads[i]->englishWord.word, lemma) == 0){
			fixSentenceLemmas(heads[i],lemma,word);
			break;
		}
		i = (i+1)%M; 
	}
}

int STinjectedLemmaLocal (char *lemma){
	
	int i = hashFunction(lemma, M);
	
	while(heads[i] != z){
		if(compareKeys(heads[i]->englishWord.word,lemma) == 0)
			return heads[i]->englishWord.sentenceLocal[0];
		
		i = (i+1)%M; 
	}
	return 0;
}

char **STinjectedLemma (char *lemma){
	
	int i = hashFunction(lemma, M);
	
	while(heads[i] != z){
		if(compareKeys(heads[i]->englishWord.word,lemma) == 0)
			return heads[i]->englishWord.sentenceArray;
		
		i = (i+1)%M; 
	}

	return NULL;
}
