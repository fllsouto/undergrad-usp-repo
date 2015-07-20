/*
//////////////////////////////////////////////////////////////////////
                        INSTANCE.C

    Modos de operação do Grafo.

\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Point.h"
#include "operation.h"
#include "Instance.h"
#define TRUE 1
#define FALSE 0
#define out_of_mem(x) {  printf("Memoria insuficiente, programa abortado!\n"); \
                         exit(x); \
                      }
#define edge_default 0.5


void searchDensity(){
    int i;
    double limConex = 0,avgConex = 0;
    
      
    for (i = 0; i < M; i++){
	limConex = lessConnectivity();
	avgConex = limConex + avgConex;
	if (out > 0 )
	    printf ("Limiar de Conexidade da Instancia p[%d] = %f\n\n-------------------------------\n\n",i,limConex);
    }
    
    avgConex = avgConex/M;
    printf ("M(d*) = %f \nMedia do limiar de conexidade de (N = %d, D = %d, M = %d) Instancia aleatorias\n",avgConex,N,dimension	,M);
 
}



int newGraph(){

    int conex = TRUE;
    point *newInst;

    newInst = createList();
    if(out == 1) 
        pointOutput(newInst,0);

    conex = searchEdge(newInst);


    free(newInst);
    return conex;

}

double lessConnectivity(){

    int conex = TRUE;
    int k = 0;
    double maxBin = 1; 
    double lessBin = 0;
    double startbin = 0.5;
    point *newInst;

    newInst = malloc(sizeof(newInst));
    newInst = createList();
    
    if(out == 1 && M == -1) 
        pointOutput(newInst,0);
    else if(out == 2)
	pointOutput(newInst,1);
	
    
    edge = startbin;
    
    while(!(maxBin - lessBin <= 0.000001)){
        conex = searchEdge(newInst);
        if (conex == TRUE){
	    maxBin = startbin;
	    startbin = (lessBin+maxBin)/2;
	    edge = startbin;
        }
        else{
	    lessBin = startbin;
	    startbin = (lessBin+maxBin)/2;	
	    edge = startbin;
        }
        k++;
    }

    free(newInst);
    return startbin;
}
