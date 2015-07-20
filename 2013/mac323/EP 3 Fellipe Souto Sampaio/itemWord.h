/*
//////////////////////////////////////////////////////////////////////
                        ITEMWORD.H

    FUNĆOES PARA MANIPULAĆÃO DA ESTRUTURA ENGLISHWORD E STRINGS NA
    ÁRVORE WORDTREE.

\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
*/


typedef char *Key;
typedef struct {
	char *word;
	char *sentenceArray;
	int *sentenceLocal;
}EnglishWord;


Key makeKey(EnglishWord );
int compareKeys (Key ,Key );
char *arrangeString(char *);
