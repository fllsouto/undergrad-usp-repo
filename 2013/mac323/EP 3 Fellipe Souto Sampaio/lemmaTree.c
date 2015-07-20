#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "lemmaTree.h"
#include "itemLemma.h"
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
	/*STprint (x);*/
    return x;
 }

static EnglishWord STinitWord(){
	EnglishWord newWord;
	newWord.word = NULL;
	newWord.sentenceArray = NULL;
	newWord.sentenceLocal = NULL;
	return newWord;
}
void STinitLemmaTree(){ 
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

/*Arruma o array de palavras que possuem um dado lema em comum*/
static void fixSentenceLemmas(link h, char *lemma,char *word){
	int treeWay = 0;
	
	treeWay = compareKeys(lemma,h->englishWord.word);
	
	if (treeWay == 0){
		char **k;
		int t;
		int f = 0;
		int quickFlag = 0;
		for (;f < h->englishWord.sentenceLocal[0]; f++){
			if (strcmp (h->englishWord.sentenceArray[f],word) == 0)
				quickFlag = 1;
		}
		
		if (!quickFlag){
			h->englishWord.sentenceLocal[0]++ ; 
			t = h->englishWord.sentenceLocal[0];
			k = (char **)realloc(h->englishWord.sentenceArray,t*sizeof(char *));
			k[t-1] = arrangeString(word);
			h->englishWord.sentenceArray = k;
		}
		return;
	}
	else if(treeWay < 0)
		fixSentenceLemmas(hl,lemma,word);
	else if (treeWay > 0)
		fixSentenceLemmas(hr, lemma,word);
	
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
int  STsearchLemmaTree(char *searchedWord){
	return seekWord (searchedWord,head);
}
/*Funćão de inserćão de palavra, lema e posićão na WordTree*/
void STappendLemmaTree(char *word,char *lemma, int sentenceNumber){
	int result = 0;
	char **senteceList = malloc(sizeof(char*));
	EnglishWord newWord;
	
	result = STsearchLemmaTree(lemma);
	if (result){
		fixSentenceLemmas(head,lemma,word);
		return;
	}
	newWord = STinitWord();
	newWord.word = arrangeString(lemma);
	senteceList[0] = arrangeString(word);
	newWord.sentenceArray = (char**)realloc(senteceList,sizeof(char*));
	newWord.sentenceLocal = malloc(sizeof(int));
	newWord.sentenceLocal[0] = 1; /*quantidade de palavras indexadas pelo mesmo lema*/
	STinsert(newWord);
}
/*Funćão de busca semelhante*/
static link seekLemmaText (char *searchedWord, link h){
	
	int treeWay = 0;
	link result;

	if (compareNodes(h,z))
		return NULL;
	
	treeWay = compareKeys(searchedWord,h->englishWord.word);
	if (treeWay == 0)
		return h;
	else if(treeWay < 0)
		result = seekLemmaText(searchedWord,hl);
	else if (treeWay > 0)
		result = seekLemmaText(searchedWord,hr);
	
	return result;	
	
}
/*Funćão de busca do algoritmo*/
char** STsearchLemmaText(char *lemma){
	link result = seekLemmaText(lemma,head);
	if (result != NULL){
		int t = result->englishWord.sentenceLocal[0];
		if (result->englishWord.sentenceArray[t] == NULL)
			return result->englishWord.sentenceArray;
		else{
			char **aux = (char**)realloc(result->englishWord.sentenceArray,(t+1)*sizeof(char*));
			aux[t] = NULL;
			result->englishWord.sentenceArray = aux;
			return result->englishWord.sentenceArray;
		}
	}
	else{
		return NULL;
	}
	
	
}

