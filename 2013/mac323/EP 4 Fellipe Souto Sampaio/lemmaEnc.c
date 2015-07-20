#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fundamentalHash.h"
#include "lemmaDefs.h"
#define TRUE 1
#define FALSE 0
typedef struct STnode *link;

struct STnode{ 
	EnglishLemma englishWord; 
	link next; 
};

static link *heads, z, *rebuild;
static int N, M, primeN;
static float load_Factor;
static int primeN;


static  link NEW(EnglishLemma newWord, link next)
{
    link x = malloc(sizeof *x);
    x->englishWord = newWord;
    x->next = next;
    
	return x;
}

static  EnglishLemma STinitCell(){
	EnglishLemma newWord;
	newWord.word = NULL;
	newWord.sentenceArray = NULL;
	newWord.sentenceLocal = NULL;
	return newWord;
}

void STinitLemmaHashing() { 
	int i;
	EnglishLemma newWord;
	N = 0;
	primeN = 0;
	M = primetable[primeN];
	newWord = STinitCell();

   	heads = malloc(M*sizeof(link));
   	z = NEW(newWord, NULL);
	for (i = 0; i < M; i++) 
		heads[i] = z; 
}

static void reinsertHash(int i,int primeFactor){
	link temp = heads[i];
	int newHash = 0;

	for (;temp != z; temp = temp->next){
		newHash = hashFunction(temp->englishWord.word,primeFactor);
		rebuild[newHash] = NEW(temp->englishWord, rebuild[newHash]);
	}
	
}

static void rebuildHash(int primeFactor){
	int i;
   	rebuild = malloc(primeFactor*sizeof(link));
	
	for (i = 0; i < primeFactor; i++) 
		rebuild[i] = z;
	
	for (i = 0; i < M; i++) 
		if (heads[i] != z)
			reinsertHash(i,primeFactor);
		
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
	heads[i] = NEW(englishWord, heads[i]); 
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


static int searchR(link t, Key v){ 
    if (t->englishWord.word == NULL) 
		return 0;
    if (compareKeys(t->englishWord.word, v) == 0)
		return 1;
    else
		return searchR(t->next, v);
}
/*diferenca entre maiusculas e minusculas*/
int STsearchLemma(char *searchedWord){ 
	int i = hashFunction(searchedWord, M);
	int temp;

	temp = searchR(heads[i], searchedWord);
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
	link temp = heads[i];
	
	for(;temp != z; temp = temp->next)
		if(compareKeys(temp->englishWord.word,lemma) == 0){
			fixSentenceLemmas(temp,lemma,word);
			break;
		}
	
}

int STinjectedLemmaLocal (char *lemma){
	
	int i = hashFunction(lemma, M);
	link temp = heads[i];
	
	for(;temp != z; temp = temp->next)
		if(compareKeys(temp->englishWord.word,lemma) == 0)
			return temp->englishWord.sentenceLocal[0];
		
	return 0;
}

char **STinjectedLemma (char *lemma){
	
	int i = hashFunction(lemma, M);
	link temp = heads[i];
	
	for(;temp != z; temp = temp->next)
		if(compareKeys(temp->englishWord.word,lemma) == 0)
			return temp->englishWord.sentenceArray;
		
	return NULL;
}
