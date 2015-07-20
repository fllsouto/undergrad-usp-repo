#ifndef _wordProb_h
#define _wordProb_h
#include "wordDefs.h"
void STinitWordHashing();
int STsearchWord(char *);
void STpreInsertWord(char *,char *,int );
void STrepetedWordInsertion(char *,int );
int *STinjectedWord (char *);

#endif