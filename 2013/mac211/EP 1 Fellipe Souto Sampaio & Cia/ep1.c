/*
Nome: Fellipe Souto Sampaio Nusp: 7990422
Nome: Caio Lopes Demario   Nusp:  7991187

MAC0211 - Labratório de programação

Prof: Kelly Rosa Braghetto
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define		nomeMax		256

int seleciona_armstrongs(char*,char*);

int main (int argc, char *argv[]){
	
    char nomeEntrada[nomeMax];
    char nomeSaida[nomeMax];
    FILE *entrada, *saida;
    int num = 0;
    int k = 10;
    double tempo_execucao;    
    clock_t inicio, fim;
 
    inicio = clock(); 
    
    strcpy(nomeEntrada,argv[1]);
    strcpy(nomeSaida,argv[2]);
    
      num = seleciona_armstrongs(nomeEntrada,nomeSaida);


    
    fim = clock();
    tempo_execucao = (double)(fim - inicio)/CLOCKS_PER_SEC;
    tempo_execucao = tempo_execucao;
    printf("Foram encontrados : %d numeros de Armstrong.\n",num);
    printf("A execucao da funcao levou %f segundos \n", tempo_execucao);

    return 0;
}