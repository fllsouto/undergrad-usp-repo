/*
//////////////////////////////////////////////////////////////////////
                        INSTANCE.C

    CRIAÇÃO DE INSTÂNCIAS E ROTINAS DE ANÁLISE DO GRAFO.

\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
*/

#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"
#include "creation.h"
#include "operation.h"
#include "Instance.h"
#include <math.h>
#define TRUE 1
#define FALSE 0
#define out_of_mem(x) {  printf("Memoria insuficiente, programa abortado!\n"); \
                         exit(x); \
                      }
#define edge_default 0.5



void searchDensity(int M,int N,int out){

    int mTimes,i;
    double density;
    double *limOut,*denseOut;
    int flag_v = 0, flag_V = 0;
    char nomeSaida[100];
    FILE *saida;

    denseOut = malloc(M*sizeof(denseOut));
    limOut = malloc(M*sizeof(limOut));

    if (!limOut)
        out_of_mem(-1);

    if (!denseOut)
        out_of_mem(-1);

    if (out == 2){
        flag_V = TRUE;
        flag_v = TRUE;
    }
    else if (out == 1)
        flag_v = TRUE;

    edge = edge_default;

    for (mTimes = 0; mTimes < M; mTimes++){


        limOut[mTimes] = lessConnectivity(N);
        density = (limOut[mTimes]*limOut[mTimes])*(N/log(N));

        denseOut[mTimes] = density;

        edge = edge_default;
    }

    density = 0;
    for (i = 0; i < M; i++)
        density = density + denseOut[i];

    density = density/M;

    if(flag_v == TRUE){
        printf ("Digite um nome para o arquivo de saida : ");
        scanf ("%s",nomeSaida);
        saida = fopen(nomeSaida,"w");
        for (i = 0; i < M; i++){
            if(flag_V == TRUE)
                fprintf(saida,"Limiar Conexivo da Instancia  #%d : %g\n",i,limOut[i]);

            fprintf (saida, "Densidade Normalizada Criticada da Instancia  #%d : %g\n\n",i,denseOut[i]);
        }
        fprintf (saida,"\nMedia final da Densidade Normalizada para (N,M) : (%d,%d) \nMf = %g\n",N,M,density);
        fclose(saida);
    }
    else{
        printf ("Densidade Normalizada Criticada\n");
        for (i = 0; i < M; i++){

            printf ("[%d] = %g\n",i, denseOut[i]);
        }
        printf ("\nMedia final da Densidade Normalizada para (N,M) : (%d,%d) \nMf = %g\n",N,M,density);

    }

    free (limOut);
    free(denseOut);
}


int newGraph(int N,int v){

    int conex = TRUE;
    Grafo *newInst;

    newInst = malloc(sizeof(newInst));

    newInst->graphList = createList(&N);


    if(v == 1)
        pointOutput(newInst->graphList, N);

    conex = searchEdge(newInst->graphList, N);


    free(newInst);
    return conex;

}


double lessConnectivity(int N){

    int conex = TRUE;
    Grafo *newInst;
    double lessEdge = sqrt(2), maxFloor = 0, x = 1;

    newInst = malloc(sizeof(newInst));

    newInst->graphList = createList(&N);


    while(x > 0.0021 ){
        conex = searchEdge(newInst->graphList, N);

        resetFlag (newInst->graphList,N);

        if (conex == TRUE){
            if (edge < lessEdge)
                lessEdge = edge;

            edge = edge*0.9;
        }
        else{
            if (edge > maxFloor)
                maxFloor = edge;
            edge = edge*0.05 + edge;
        }
        x = lessEdge-maxFloor;
    }


    seed = (ceil(newInst->graphList[0].x*newInst->graphList[0].y*rand()));
    free(newInst);
    return lessEdge;



}
