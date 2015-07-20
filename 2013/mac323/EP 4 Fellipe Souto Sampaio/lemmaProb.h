#ifndef _lemmaProb_h
#define _lemmaProb_h
#include "lemmaDefs.h"
void STinitLemmaHashing();
int STsearchLemma(char *);
void STpreInsertLemma(char *,char *,int );
void STrepetedLemmaInsertion(char *,char *);
char **STinjectedLemma (char *);
int STinjectedLemmaLocal (char *);

#endif