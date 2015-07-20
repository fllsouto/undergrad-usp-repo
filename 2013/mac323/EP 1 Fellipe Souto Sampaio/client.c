/*
 \__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__


  Nome:     Fellipe Souto Sampaio
  NUSP:     7990422

  Prof:     Yoshiharu Kohayakawa
  Disciplina: MAC0323 - Estrutura de dados


  LIMIAR DE CONEXIDADE PARA CERTOS GRAFOS GEOMÉTRICOS I
  -client.c
  -Graph.h
  -Instance.c
  -Instance.h
  -creation.c
  -creation.h
  -operation.c
  -operation.h
  -RelatórioEP1.pdf
  -makefiless

  Abril de 2013.
 \__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__
*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>


/*
//////////////////////////////////////////////////////////////////////
  1. MÓDULOS EXTERNOS

\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
*/
#include "Instance.h"

/*
//////////////////////////////////////////////////////////////////////
  2. MACROS E CONSTANTES

\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
*/

#define out_of_mem(x) {  printf("Memoria insuficiente, programa abortado!\n"); \
                         exit(x); \
                      }
#define TRUE 1
#define FALSE 0
#define edge_default 0.5

/*
//////////////////////////////////////////////////////////////////////
  3. VARIÁVEIS GLOBAIS

\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
*/

double edge = 0;
float seed = -1;

/*
//////////////////////////////////////////////////////////////////////
  4. PROTÓTIPOS DE FUNÇÕES IMPLEMENTADAS

\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
*/

void getArgv(int argc,char *argv[],int *N,double *d,float *s,int *v, int *C, int *m);

/*
//////////////////////////////////////////////////////////////////////
  5. MAIN

\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
*/

int main (int argc,char *argv[]){

    char *prog_name;
    int N = -1 ,out = 0, C = 0, M = 0, conex = TRUE;
    clock_t inicio, fim;
    double exec , lessEdge = 0;

    inicio = clock();

    prog_name = argv[0];

    getArgv(argc, argv, &N, &edge, &seed, &out,&C,&M);

    printf ("\nInformacoes fornecidas, Prog : %s , N : %d , d : %g , s : %f , v : %d  M : %d , C : %d\n",prog_name,N,edge,seed,out, M,C);



    if (M != 0)
        searchDensity(M,N,out);
    else
    {
        if (C != 2)
        {
            if (C == 1)
                N = -1;

            conex = newGraph(N,out);

            if (conex == TRUE)
                printf ("O grafo e' conexo\n");
            else
                printf ("O grafo nao e' conexo\n");
        }
        else{


            edge = edge_default;
            lessEdge = lessConnectivity(N);

            printf ("O menor d para o grafo ser conexo e' = %g\n",lessEdge);


        }
    }
    fim = clock();

    exec = (double)(fim-inicio);
    printf ("A execucao levou %f segundos \n",exec/1000000);
    return 0;
}

/*
//////////////////////////////////////////////////////////////////////
  6. LEITURA DOS PARÂMETROS ARGV

\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
*/

void getArgv(int argc,char *argv[],int *N,double *d,float *s,int *v, int *C,int *M){

    while (--argc){
        if (strcmp(argv[argc],"-v") == 0)
            *v = 1;
        else if (strcmp(argv[argc],"-D") == 0)
            *C = 2;
        else if (strcmp(argv[argc],"-V")==0)
            *v = 2;
        else if (strcmp(argv[argc],"-C")==0)
            *C = 1;
        else if (sscanf((argv[argc]),"-s%f",s) == 1) ;
        else if (sscanf((argv[argc]),"-M%d",M) == 1) ;
        else if (sscanf((argv[argc]),"-d%lf",d) == 1) ;
        else if (sscanf((argv[argc]),"-N%d",N) == 1) ;
        else{
            printf ("Formato correto de entrada : %s [-Nxxx] [-dxxx] [-sxxx] [-v]\n",argv[0]); /*melhorar isso depois*/
            exit (EXIT_FAILURE);
            }
    }
}

