/*
 \__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__


  Nome:     Fellipe Souto Sampaio
  NUSP:     7990422

  Prof:     Yoshiharu Kohayakawa
  Disciplina: MAC0323 - Estrutura de dados


  LIMIAR DE CONEXIDADE PARA CERTOS GRAFOS GEOMÉTRICOS II
  -client.c
  -Instance.c
  -Instance.h
  -operation.c
  -operation.h
  -Point.h
  -Point.S.c
  -Point.C.c
  -RelatórioEP2.pdf
  -makefile

  Maio de 2013.
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
#include "Instance.h"

/*
//////////////////////////////////////////////////////////////////////
  3. VARIÁVEIS GLOBAIS

\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
*/
int out = 0;
double edge = 0;
float seed = -1;
int dimension;
int N = -1;
int C = -1;
int M = -1;/*acessível aos outros?*/

/*
//////////////////////////////////////////////////////////////////////
  4. PROTÓTIPOS DE FUNÇÕES IMPLEMENTADAS

\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
*/

void getArgv(int argc,char *argv[]);

/*
//////////////////////////////////////////////////////////////////////
  5. MAIN

\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
*/

int main (int argc,char *argv[]){

    char *prog_name;
    int conex = TRUE;
    clock_t inicio, fim;
    double exec;
    double lessEdge = 0;
    
    inicio = clock();

    prog_name = argv[0];

    getArgv(argc, argv);

    printf ("Informacoes fornecidas \nProg : %s \nDimension : %d \nN : %d  \nd : %g \ns : %f  \nv : %d \nM : %d  \nC : %d\n",prog_name,dimension,N,edge,seed,out, M,C);
    
    if (M >0){
      searchDensity();
    }
    else if (C != 2){
	    conex = newGraph();
	    if (conex == TRUE)
	      printf ("O grafo e' conexo\n");
	    else
	      printf ("O grafo nao e' conexo\n");
	
	}
	else{
	    lessEdge =  lessConnectivity();
	    printf ("O limiar de conexidade do grafo e' edge = %f\n",lessEdge);
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

void getArgv(int argc,char *argv[]){

    while (--argc){
        if (strcmp(argv[argc],"-v") == 0)
            out = 1;
        else if (strcmp(argv[argc],"-L") == 0)
            C = 2;
        else if (strcmp(argv[argc],"-V")==0)
            out = 2;
        else if (strcmp(argv[argc],"-C")==0)/*?*/
            C = 1;
        else if (sscanf((argv[argc]),"-s%f",&seed) == 1) ;        
	else if (sscanf((argv[argc]),"-D%d",&dimension) == 1) ;
        else if (sscanf((argv[argc]),"-M%d",&M) == 1) ;
        else if (sscanf((argv[argc]),"-d%lf",&edge) == 1) ;
        else if (sscanf((argv[argc]),"-N%d",&N) == 1) ;
        else{
            printf ("Formato correto de entrada : %s [-Nxxx] [-dxxx] [-sxxx] [-v]\n",argv[0]); /*melhorar isso depois*/
            exit (EXIT_FAILURE);
            }
    }
}

