#include <sys/types.h>
#include <sys/wait.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#define NIT 200000000


double f(double a)
{
    return (4.0 / (1.0 + a*a));
}

typedef double  *SHARED;

SHARED x;

int main(int ac, char  **av)
{
  unsigned long long int i;
  int ii;
  int smid;
  double h = 1./NIT;
  double mypi;
  int nprocs=1;
  double sum = 0.0;
  
  if (ac>1) 
	nprocs = atoi(av[1]);
  if (nprocs < 1) nprocs = 1;

  smid = shmget(IPC_PRIVATE, sizeof(double)*nprocs, IPC_CREAT | 0600);
  if (smid == -1) {
	perror("Erro de alocação");
	return 1;
  }

  x = (SHARED)shmat(smid, 0, 0);
  
  for (ii=1;ii<nprocs;ii++) {
	if ((fork()) == 0) { 
	  printf("Iniciando filho %d\n", ii);
	  for (i=ii; i< NIT; i+=nprocs) {
		mypi = h * ((double)i + 0.5);
		sum += f(mypi);
	  }
	  mypi = h * sum;
	  
	  x[ii] = mypi;
	  return 0;
	}
  }

  for (i=0; i< NIT; i+=nprocs) {
	mypi = h * ((double)i + 0.5);
	sum += f(mypi);
  } 
  mypi = h * sum;

  /* espera cada um dos filhos terminar */
  for (i=1;i<nprocs;i++) {
	wait(NULL);
  }  

  for (i=1;i<nprocs;i++) {
	mypi += x[i];
  }  

  printf("\n\npi = %.8f\n", mypi);
  shmctl(smid,IPC_RMID, NULL);
  return 0;
}



