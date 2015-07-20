#ifndef _wordEnc_h
#define _wordEnc_h
#include "wordDefs.h"
void STinitWordHashing();
int STsearchWord(char *);
void STpreInsertWord(char *,char *,int );
void STrepetedWordInsertion(char *,int );
int *STinjectedWord (char *);

#endif