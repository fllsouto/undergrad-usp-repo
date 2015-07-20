#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "lemmaTree.h"
#include "itemWord.h"
#define hl  (h->l)
#define hr  (h->r)
#define hrl  (h->r->l)
#define hll  (h->l->l)

typedef struct STnode* link;
/*Estrutura de dados do nó da árvore*/
struct STnode{ 
	EnglishWord englishWord; 
	link r;
	link l;
	int red; 
	
};

static link head, z; 

/*Funćões de criaćão e inserćão na ARNE*/

static link NEW(EnglishWord newWord, link l, link r, int red){
	link x = malloc(sizeof *x);
    x->englishWord = newWord;  
	x->r = r;  
	x->l = l;
	x->red = red;
    return x;
 }

static EnglishWord STinitWord(){
	EnglishWord newWord;
	newWord.word = NULL;
	newWord.sentenceArray = NULL;
	newWord.sentenceLocal = NULL;
	return newWord;
}
void STinitWordTree(){ 
	EnglishWord newWord;
	
	newWord = STinitWord();
	
	head = (z = NEW(newWord, NULL, NULL, 0));
}

static link rotL(link h){ 
	link x = hr; 
	hr = x->l; 
    x->l= h;
	x->red = h->red; 
	h->red = 1;
	return x;
 }

static link rotR(link h){ 
	link x = hl; 
	hl = x->r;
	x->r = h;
	x->red = h->red; 
	h->red = 1;
	return x;
}

static void colorFlip(link h){ 
	h->red = 1 - h->red;
	hl->red = 1 - hl->red;
	hr->red = 1 - hr->red;    
}

/*compara se dois nodes são iguais*/
static int compareNodes(link h,link z){
	
	if(h->englishWord.word == z->englishWord.word &&  h->r == z->r && h->l == z->l && h->red == z->red)
		return 1;
	else
		return 0;
}

static link LLRBinsert(link h, EnglishWord newWord){ 
	Key v = makeKey(newWord);
	int val = 0;

	if (compareNodes(h,z))
		return NEW(newWord, z, z, 1);
	
	val = compareKeys(v,makeKey(h->englishWord));
	if ( val < 0)
		hl = LLRBinsert(hl, newWord);
    else
		hr = LLRBinsert(hr, newWord);
    if (hr->red && !hl->red)
		h = rotL(h);
    if (hl->red && hll->red) 
		h = rotR(h);
    if (hl->red && hr->red) 
		colorFlip(h);

	return h;
}

static void STinsert(EnglishWord newWord){
	head = LLRBinsert(head, newWord);
	head->red = 0;
}

/*Arruma a posicão da sentenća word */
static void fixSentenceNumber(link h, char *word,int newPosition){
	int treeWay = 0;
	
	treeWay = compareKeys(word,h->englishWord.word);
	
	if (treeWay == 0){
		int *k;
		int t;
		h->englishWord.sentenceLocal[0]++ ; 
		t = h->englishWord.sentenceLocal[0];
		k = (int *)realloc(h->englishWord.sentenceLocal,t*sizeof(int));
		k[t-1] = newPosition;
		h->englishWord.sentenceLocal = k;
		return;
	}
	else if(treeWay < 0)
		fixSentenceNumber(hl, word,newPosition);
	else if (treeWay > 0)
		fixSentenceNumber(hr, word,newPosition);
	
}

/*Procura por uma palavra dentro da árvore*/
static int seekWord (char *searchedWord, link h){
	int treeWay = 0;
	int result = 0;

	if (compareNodes(h,z))
		return 0;
	
	treeWay = compareKeys(searchedWord,h->englishWord.word);
	if (treeWay == 0)
		return 1;
	else if(treeWay < 0)
		result = seekWord(searchedWord,hl);
	else if (treeWay > 0)
		result = seekWord(searchedWord,hr);
	
	return result;
	
}
/*Funćão de busca do cliente*/
int  STsearchWordTree(char *searchedWord){
	return seekWord (searchedWord,head);
}
/*Funćão de inserćão de palavra, lema e posićão na WordTree*/
void STappendWordTree(char *word,char *lemma, int sentenceNumber){
	int *k = malloc(2*sizeof(int));
	int result = 0;
	EnglishWord newWord;
	
	result = STsearchWordTree(word);
	if (result){
		fixSentenceNumber(head,word,sentenceNumber);
		return;
	}
	k[0] = 2;
	k[1] = sentenceNumber;
	newWord = STinitWord();
	
	newWord.word = arrangeString(word);
	newWord.sentenceArray = arrangeString(lemma);
	newWord.sentenceLocal = (int*)realloc(k,k[0]*sizeof(int));
	STinsert(newWord);

}
/*Funćão de busca semelhante*/
static link seekWordText (char *searchedWord, link h){
	int treeWay = 0;
	link result;

	if (compareNodes(h,z))
		return NULL;
	
	treeWay = compareKeys(searchedWord,h->englishWord.word);
	if (treeWay == 0)
		return h;
	else if(treeWay < 0)
		result = seekWordText(searchedWord,hl);
	else if (treeWay > 0)
		result = seekWordText(searchedWord,hr);
	
	return result;	
}
/*Funćão de busca do algoritmo*/
int* STsearchWordText(char *word){
	
	link result = seekWordText (word,head);
	if (result != NULL){
		return result->englishWord.sentenceLocal;
	}
	else{
		return NULL;
	}
}





