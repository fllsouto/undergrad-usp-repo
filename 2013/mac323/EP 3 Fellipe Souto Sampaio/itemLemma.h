/*
//////////////////////////////////////////////////////////////////////
                        ITEMLEMMA.H

    FUNĆOES PARA MANIPULAĆÃO DA ESTRUTURA ENGLISHWORD E STRINGS NA
    ÁRVORE LEMMATREE.

\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
*/


typedef char *Key;
typedef struct {
	char *word; /*chave*/
	char **sentenceArray;
	int *sentenceLocal;
}EnglishWord;


Key makeKey(EnglishWord );
int compareKeys (Key ,Key );
char *arrangeString(char *);
