#include <stdio.h>
#include "wordProb.h"
#include "wordEnc.h"
#include "handlingWord.h"


void SThandlingWord(char *word,char *lemma, int position){
	int insertChance = STsearchWord (word);
	
	if (!insertChance)
		STpreInsertWord(word, lemma, position);
	else
		STrepetedWordInsertion(word, position);
}