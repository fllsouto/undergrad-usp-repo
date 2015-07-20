#include <stdio.h>

#define TAM 10000
double a[TAM][TAM] = {0.,};

int main()
{
  int i, j;
  double x;
  for(i=0; i< TAM; i++)
    for(j=0; j< TAM; j++)
      a[i][j] = i*j;
  return 0;
}
