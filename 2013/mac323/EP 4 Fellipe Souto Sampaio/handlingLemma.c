#include "handlingLemma.h"
#include "lemmaEnc.h"
#include "lemmaProb.h"

void SThandlingLemma(char *lemma,char *word,int position){
	int insertChance = STsearchLemma (lemma);
	
	if (!insertChance)
		STpreInsertLemma(lemma, word, position);
	else
		STrepetedLemmaInsertion(lemma, word);
}

