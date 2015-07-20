/*
//////////////////////////////////////////////////////////////////////
                        OPERATION.C

    ALGORITMO DE CONEXIDADE, CRIAÇÃO DO VETOR DE RAMIFICAÇÕES,
    RELAÇÕES BINÁRIAS, ARRANJO DO VETOR DE RAMIFICAÇÕES.

\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Point.h"
#include "operation.h"
#define TRUE 1
#define FALSE 0
#define out_of_mem(x) {  printf("Memoria insuficiente, programa abortado!\n"); \
                         exit(x); \
                      }

int searchEdge (point *gList){


    int i,k;
    int conex = TRUE;
    int *adjVector, *flagList;
    int connectIndx;
    flagList = initVector(FALSE);
    adjVector = initVector(-1);

    for(i = 0; i < N; i++){
        for (k = i+1; k < N; k++){
            if(adjVector[i] == adjVector[k] && adjVector[i] != -1){
		k++;
	    }
            else if(nodeConex(gList[i],gList[k])){
                    binRelat(adjVector,&flagList[i],&flagList[k],i,k);
		  }
        }
    }

    connectIndx = adjVector[0];
    if (connectIndx != -1){
        for (i = 0; i < N; i++){
            if(connectIndx != adjVector[i]){
                conex = FALSE;
                break;
            }
        }
    }
    else
        conex = FALSE;


    free(adjVector);
    free(flagList);
    return conex;

}


int *initVector(int k){

    int *v,i;
    v = malloc(N*sizeof(v));

    if (!v)
        out_of_mem(-1);

    for (i = 0; i < N; i++)
        v[i] = k;

    return v;
}


int nodeConex (point a, point b){ /*usar do módulo points*/

    if (distance(a,b) <= edge){
	return TRUE;
    }
    else{
	return FALSE;
    }
}


void binRelat(int *adjVector, int* flagA, int* flagB, int i, int k){ /*critical point do algoritmo*/

    if(!*flagA && !*flagB){
	*flagA = TRUE;
        *flagB = TRUE;
        adjVector[i] = i;
        adjVector[k] = i;
    }
    else{
        if(!*flagB){
            *flagB = TRUE;
            adjVector[k] = adjVector[i];
        }
        else{
            if(!*flagA){
               *flagA = TRUE;
               adjVector[i] = adjVector[k];
            }
            else{
                arrangeList(adjVector, adjVector[i],adjVector[k]);
            }
        }
    }

}

void arrangeList(int *adjVector,int i,int k){

    int j;
    for (j = 0; j < N; j++)
        if (adjVector[j] == k)
            adjVector[j] = i;

}

