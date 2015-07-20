/*
//////////////////////////////////////////////////////////////////////
                        CREATION.C

            CRIAÇÃO DO GRAFO, PONTOS E RESET DE FLAGS.

\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
*/


#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"
#include "creation.h"
#include <math.h>
#define TRUE 1
#define FALSE 0
#define out_of_mem(x) {  printf("Memoria insuficiente, programa abortado!\n"); \
                         exit(x); \
                      }
#define seed_miss  314
#define maxNome 128

point *createList(int *N){

    point *gList;
    int i = 0,auxCont = 0;
    char nomeEntrada[maxNome],aux[maxNome];
    FILE *entrada;

    if (*N == -1){
        printf ("Quantos pontos existem no arquivo de entrada ? : " );
        scanf("%d", N);
        gList = malloc(*N*sizeof(*gList));

        if (!gList)
            out_of_mem(-1);

        printf ("Insira o nome da entrada : \n");
        scanf ("%s",nomeEntrada);

        entrada = fopen(nomeEntrada,"r");

        if (entrada == NULL)
        {
            fprintf(stderr, "ERRO!! Nao consegui abrir o arquivo %s\n", nomeEntrada);
            exit(-1);
        }

        while(fgets(aux,maxNome,entrada)){

            sscanf (aux,"%f %f", &gList[i].x, &gList[i].y);
            gList[i].initFlag = FALSE;
            i++;
        }
        fclose(entrada);
        return gList;
    }
    else {
        gList = malloc(*N*sizeof(*gList));

        if (!gList)
            out_of_mem(-1);

        if (seed == -1)
            seed = seed_miss;

        srand(ceil(seed));

        for (i = 0; i< *N; i++, auxCont++){
            gList[i] = r_point();
            if(auxCont == 200){
                srand(ceil(gList[i].x + gList[i].y));
                auxCont = 0;
            }
        }

        return gList;
    }

}


point r_point(){
    point a;

    a.x = 1.0*rand()/RAND_MAX;
    a.y = 1.0*rand()/RAND_MAX;
    a.initFlag = FALSE;

    return a;
}


void resetFlag (point *gList,int N){

    int i;

    for (i = 0; i < N; i++)
        gList[i].initFlag = FALSE;


}


