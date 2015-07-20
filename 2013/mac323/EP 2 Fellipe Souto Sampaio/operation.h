/*
//////////////////////////////////////////////////////////////////////
                        OPERATION.H

                ARQUIVO HEADER DE OPERATION.C .

\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
*/
void arrangeList(int *adjVector,int i,int k);
void binRelat(int *adjVector, int* flagA, int* flagB, int i, int k);
int nodeConex (point a, point b);
int *initVector(int k);
int searchEdge (point *gList);

extern double edge;
extern float seed;
extern int N;
