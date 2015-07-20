#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fundamentalHash.h"
#include "wordDefs.h"
#define TRUE 1
#define FALSE 0
typedef struct STnode *link;

struct STnode{ 
	EnglishWord englishWord; 
	link next; 
};

static link *heads, z, *rebuild;
static int N, M, primeN;
static float load_Factor;
static int primeN;


static link NEW(EnglishWord newWord, link next)
{
    link x = malloc(sizeof *x);
    x->englishWord = newWord;
    x->next = next;
    
	return x;
}

static EnglishWord STinitCell(){
	EnglishWord newWord;
	newWord.word = NULL;
	newWord.sentenceArray = NULL;
	newWord.sentenceLocal = NULL;
	return newWord;
}

void STinitWordHashing(){ 
	int i;
	EnglishWord newWord;
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

static Key hashKey(EnglishWord newWord){
	Key aux;
	aux = malloc((int)strlen(newWord.word)*sizeof(char));
	strcpy (aux,newWord.word);
	return aux;
}

static void STinsert(EnglishWord englishWord){
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

void STpreInsertWord(char *word,char *lemma,int sentenceNumber){
	
	int *k = malloc(2*sizeof(int));
	EnglishWord newWord;
	k[0] = 2;
	k[1] = sentenceNumber;
	newWord = STinitCell();
	
	newWord.word = arrangeString(word);
	newWord.sentenceArray = arrangeString(lemma);
	newWord.sentenceLocal = (int*)realloc(k,k[0]*sizeof(int));
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
int STsearchWord(char *searchedWord){ 
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


static void fixSentenceNumber(link h, char *word,int newPosition){

	int *k;
	int t;
	h->englishWord.sentenceLocal[0]++ ; 
	t = h->englishWord.sentenceLocal[0];
	k = (int *)realloc(h->englishWord.sentenceLocal,t*sizeof(int));
	k[t-1] = newPosition;
	h->englishWord.sentenceLocal = k;
}

void STrepetedWordInsertion(char *word,int position){
	
	int i = hashFunction(word, M);
	link temp = heads[i];
	
	for(;temp != z; temp = temp->next)
		if(compareKeys(temp->englishWord.word,word) == 0){
			int t = temp->englishWord.sentenceLocal[0];
			if (temp->englishWord.sentenceLocal[t-1] != position) /*Elimina repetićões na lista de sentenćas*/
				fixSentenceNumber(temp,word,position);
			break;
		}
	
}

int *STinjectedWord (char *word){
	
	int i = hashFunction(word, M);
	link temp = heads[i];
	
	for(;temp != z; temp = temp->next)
		if(compareKeys(temp->englishWord.word,word) == 0)
			return temp->englishWord.sentenceLocal;
		
	return NULL;
}

