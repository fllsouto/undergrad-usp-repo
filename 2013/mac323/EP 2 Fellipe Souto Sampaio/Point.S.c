/*
//////////////////////////////////////////////////////////////////////
                        Point.S.c

  Interface para manipulação de grafos em uma hiperesfera.

\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
*/


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Point.h"
#define out_of_mem(x) {  printf("Memoria insuficiente, programa abortado!\n"); \
                         exit(x); \
                      }
#define seed_miss  314
#define maxNome 128
#define TRUE 1
#define FALSE 0

void Randomize(int newseed){
    srand(newseed);
}

int InteiroRandomico(int min, int max){
    int k;
    double d;


    d = (double) rand();
    d = d/ ((double) RAND_MAX + 1);
    k = (int) (d * (max - min + 1));
    return (min + k);
}


double RealRandomico(double min, double max){
    double d;

    d = (double) rand() / ((double) RAND_MAX + 1);
    return (min + d * (max - min));
}

point randPoint(){

    double *point;
    double *temppoint;
    double r_sqrt = 0;
    double lambda = 0;
    double interval = 1;
    double validation = 0;
    
    int i = 0;
    double l;
    point = malloc(dimension*sizeof(double));
    temppoint = malloc(dimension*sizeof(double));
    l = (double)(dimension);
    for (i = 0, l = dimension; i <dimension; i++,l--){
	
      interval = 1/l;
        temppoint[i] = RealRandomico((-1)*interval,interval);
	
        r_sqrt = temppoint[i]*temppoint[i] + r_sqrt;
    }
    
    lambda = sqrt(0.25/r_sqrt);
    
    for (i = 0; i< dimension; i++){
        point[i] = temppoint[i]*lambda;
    }
    
    for (i = 0; i< dimension; i++){
        validation = point[i]*point[i] + validation;
    }
    
    Randomize((int)((point[dimension-1])*1000));
    free(temppoint);
    return point;
}

point *createList(){

    point *pointList;
    int i = 0,k = 0;
    double r_sqrt,lambda, validation;
    double tempCord;
    double seedReset = 0;

    if (N == -1){
        printf ("Quantos pontos deseja criar ? : " );
        scanf("%d", &N);
        pointList = malloc(N*sizeof(point*));

        if (!pointList)
            out_of_mem(-1);

	for (i = 0; i < N; i++){
	    
	    pointList[i] = malloc(dimension*sizeof(double));

	    k = 0;
	    r_sqrt=0;
	    while(k < dimension){
		printf ("X%d: ",k);
		scanf ("%lf",&tempCord);
	      
		if (tempCord >= -1 && tempCord <= 1){
		    pointList[i][k] = tempCord;
		    r_sqrt = pointList[i][k]*pointList[i][k] + r_sqrt; 
		    k++;
		}
		else
		    printf ("a Coordenada inserida deve estar no intervalo [-1,1]\n");
	      
	    }
	    
	    lambda = sqrt(0.25/r_sqrt);
	    for (k = 0, validation = 0; k< dimension; k++){
		pointList[i][k] = pointList[i][k]*lambda;
		validation = pointList[i][k]*pointList[i][k] + validation;
	    }  
	}
	printf ("Pontos inseridos com sucesso! \n"); 
        return pointList;
    }
    else {
        pointList = malloc(N*sizeof(point*));

        if (!pointList)
            out_of_mem(-1);

        if (seed == -1)
            seed = seed_miss;

        Randomize(ceil(seed*dimension));
        for (i = 0; i< N; i++){
            pointList[i] = randPoint();
        }
        seedReset = InteiroRandomico(N*dimension*(-1),N*dimension*(-1)*seed);
	seed = seedReset;
        
    
	return pointList;
    }

}

double distance(point a,point b){
  
  int tmpDim = dimension;
  int i;
  double euclidianNorm = 0;
  
  
  for (i = 0; i < tmpDim; i++){
      euclidianNorm = (a[i] - b[i])*(a[i] - b[i]) + euclidianNorm;
  }
  euclidianNorm = sqrt(euclidianNorm);
  return euclidianNorm;
  
  
}


void pointOutput(point *gList, int op){ 	

    FILE *saida;
    char nomeSaida[100];
    int i,k;
    
    if (op == 0){
	printf ("Digite um nome para a saida : ");
	scanf ("%s", nomeSaida);

	saida = fopen(nomeSaida, "w");

	if (saida == NULL) {
	    printf("\nNao foi possivel criar o arquivo : %s.\n\n", nomeSaida);
	    exit(-1);
	}
	for(i = 0; i < N; i++){
	  fprintf (saida, "#%d ... ( %f ",i,gList[i][0]);
	  for(k = 1; k < dimension; k++) 
	    fprintf (saida, ", %f",gList[i][k]);
	  
	  fprintf (saida, " )");
	  fprintf (saida, "\n\n");
      
	}
	
	fclose(saida);
    }
    else{
      	for(i = 0; i < N; i++){
	    printf ("#%d ... ( %f ",i,gList[i][0]);
	    for(k = 1; k < dimension; k++) 
	      printf (", %f",gList[i][k]);
	    
	    printf (" )");
	    printf ("\n\n");
      
	}
    }
}