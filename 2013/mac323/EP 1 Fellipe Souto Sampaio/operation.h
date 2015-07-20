/*
//////////////////////////////////////////////////////////////////////
                        OPERATION.H

                ARQUIVO HEADER DE OPERATION.C .

\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
*/

int searchEdge (point *gList, int N);
void arrangeList(int *adjVector,int i,int k, int N);
int distance (point a, point b);
void binRelat(int *adjVector, point *A, point *B, int i, int k, int N);
void pointOutput(point *gList, int N);
int *initVector(int N);



extern double edge;
extern float seed;
