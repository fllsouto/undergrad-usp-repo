#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>

typedef void* (*FPTR)(void *);

#define NIT 200000000
#define MAX_THR 32

double pi[MAX_THR];
int NT = 1;

double f(double a)
{
  return (4.0 / (1.0 + a*a));
}


void *t(void *nn)
{
  unsigned long long int i;
  int n = (int) nn;				/* feio */
  double h = 1./NIT;
  double mypi;
  double sum = 0.0;

  for (i = n; i< NIT; i += NT) {
        mypi = h * ((double)i - 0.5);
        sum += f(mypi);
  }
  pi[n] = h * sum; 

  return NULL;
}

int main(int ac, char **av)
{
  pthread_t id[MAX_THR];
  void *retval;
  int  i;

  double res = 0.;

  if (ac > 1) {
	NT = atoi(av[1]);
	if (NT < 1) NT = 1;
	else if (NT > MAX_THR) NT=MAX_THR;
  }

  for (i=0; i<NT; i++)
	pthread_create(&id[i], NULL, t, (void *)i); /* feio */

  for (i=0; i<NT; i++)
	if (pthread_join(id[i], &retval)) {
	  fprintf(stderr, " >>> Thread %d falhou\n", i);
	  exit(1);
	}

  for (i=0; i<NT; i++) res += pi[i];
  printf("pi = %g\n", res);

  return 0;
}
