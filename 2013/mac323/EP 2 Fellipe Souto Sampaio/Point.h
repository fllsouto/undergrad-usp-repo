/*
//////////////////////////////////////////////////////////////////////
                        Point.h

  Header abstrato para manipulação de grafo em subconjuntos do R^d.

\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
*/


typedef double *point;
point randPoint();
double distance(point, point);
void Randomize(int seed);
double RealRandomico(double min, double max);
int InteiroRandomico(int min, int max);
point *createList();
void pointOutput(point *gList,int op);


extern float seed;
extern int N;
extern int dimension;
/*solução para randPoint void é usar extern em dimension*/
