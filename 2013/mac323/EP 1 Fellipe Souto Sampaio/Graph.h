/*
//////////////////////////////////////////////////////////////////////
                        GRAFO.H

    DEFINIÇÃO DA ESTRUTURA DE DADOS GRAFO E DA ESTRUTURA DE DADOS PONTO.

\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
*/



typedef  struct{

    float x;
    float y;
    int initFlag;

} point;

typedef struct {
    point *graphList;

}Grafo;
