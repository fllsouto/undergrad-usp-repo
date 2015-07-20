/*
//////////////////////////////////////////////////////////////////////
                        CREATION.C

    ALGORITMO DE CONEXIDADE, CRIAÇÃO DO VETOR DE RAMIFICAÇÕES,
    CÁLCULO DA DISTÂNCIA, RELAÇÕES BINÁRIAS, ARRANJO DO VETOR DE
    RAMIFICAÇÕES E IMPRESSÃO DA LISTA DE PONTOS.

\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
*/

#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"
#include "operation.h"
#include <math.h>
#define TRUE 1
#define FALSE 0
#define out_of_mem(x) {  printf("Memoria insuficiente, programa abortado!\n"); \
                         exit(x); \
                      }

int searchEdge (point *gList, int N){


    int i,k;
    int conex = TRUE;
    int *adjVector;
    int connectIndx;
    adjVector = initVector(N);

    for(i = 0; i < N; i++){
        for (k = i+1; k < N; k++){
            if(adjVector[i] == adjVector[k] && adjVector[i] != -1)
                k++;
            else if(distance(gList[i],gList[k]))
                    binRelat(adjVector,&gList[i],&gList[k],i,k, N);
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

    /*for (i = 0; i<N; i++)
        printf ("[%d] = %d\n",i,adjVector[i]);*/

    free(adjVector);
    return conex;

}


int *initVector(int N){

    int *v,i;
    v = malloc(N*sizeof(v));

    if (!v)
        out_of_mem(-1);

    for (i = 0; i < N; i++)
        v[i] = -1;

    return v;
}


int distance (point a, point b){

    double dx = a.x - b.x;
    double dy = a.y - b.y;

    if (sqrt(dx*dx + dy*dy) <= edge)
        return TRUE;
    else
        return FALSE;
}


void binRelat(int *adjVector, point *A, point *B, int i, int k, int N){

   /* int j;*/

    if(!A->initFlag && !B->initFlag){
        A->initFlag = TRUE;
        B->initFlag = TRUE;
        adjVector[i] = i;
        adjVector[k] = i;
    }
    else{
        if(!B->initFlag){
            B->initFlag = TRUE;
            adjVector[k] = adjVector[i];
        }
        else{
            if(!A->initFlag){
               A->initFlag = TRUE;
               adjVector[i] = adjVector[k];
            }
            else{
                arrangeList(adjVector, adjVector[i],adjVector[k], N);
                }
        }
    }

     /*  for (j = 0; j < N; j++)
        printf ("%d ",adjVector[j]);

    printf ("\n");*/

}


void pointOutput(point *gList, int N){

    FILE *saida;
    char nomeSaida[100];
    int i;

    printf ("Digite um nome para a saida : ");
    scanf ("%s", nomeSaida);

    saida = fopen(nomeSaida, "w");

    if (saida == NULL) {
        printf("\nNao foi possivel criar o arquivo : %s.\n\n", nomeSaida);
        exit(-1);
    }
    else
        printf("\n");

    for (i = 0; i < N; i++)
        fprintf (saida, "#%d ... (%f,%f)\n",i, gList[i].x, gList[i].y);

    fclose(saida);

}


void arrangeList(int *adjVector,int i,int k,int N){

    int j;

    for (j = 0; j < N; j++)
        if (adjVector[j] == k)
            adjVector[j] = i;

}

