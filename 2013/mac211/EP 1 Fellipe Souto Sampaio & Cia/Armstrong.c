/*
Nome: Fellipe Souto Sampaio Nusp: 7990422
Nome: Caio Lopes Demario   Nusp:  7991187

MAC0211 - Labratório de programação

Prof: Kelly Rosa Braghetto
*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

int seleciona_armstrongs(char* nome_arq_entrada, char* nome_arq_saida);


int main(int argc, char* argv[])
{
    int a;
    clock_t inicio, fim;
    double tempo_execucao;
    inicio = clock(); /* marca o horario de inicio da execucao */

    printf("Ha %d numeros de Armstrong!\n",seleciona_armstrongs(argv[1],argv[2]));

    fim = clock(); /* marca horario de fim da execucao */
    tempo_execucao = (double)(fim - inicio) / CLOCKS_PER_SEC;
    printf("A execucao da funcao levou %f segundos \n", tempo_execucao);
    return 0;
}

int seleciona_armstrongs(char* nome_arq_entrada, char* nome_arq_saida)
{
    /*cria arquivos de entada e saida*/
    FILE *entrada;
    FILE *saida;
    unsigned int n, N, k, i, digito, qtd;
    /**/
    char num[11];

    k = 0;
    qtd = 0;
    /*abre o arquivo de entrada para leitura*/
    entrada = fopen(nome_arq_entrada, "r");
    /*abre o arquivo de saida*/
    saida = fopen(nome_arq_saida, "w");

    if (saida == NULL)
    {
        printf("\nNao foi possivel criar o arquivo %s.\n\n", nome_arq_saida);
        exit(-1);
    }

    if (entrada == NULL)
    {
        fprintf(stderr, "Não foi possivel abrir o arquivo %s\n", nome_arq_entrada);
        exit(-1);
    }

    /*varre o arquivo até o fim*/
    while(fscanf(entrada,"%s", num) != EOF)
    {
        i = 0;
        k = 0;
        /* n é a variavel que armazena a quantidade de digitos*/
        n = strlen(num);
        /*N é a variavel que armazena o número lido*/
        N = atoi(num);

        while(i < n)
        {
            /*Converte o dígito i para int*/
            digito = num[i] - '0';
            /*a cada iteração incrementa o valor de k com o proximo digito elevado a n*/
            k += pow(digito,n);
            i++;
        }
        if(k == N)
        {
            /*se o valor da soma dos digitos elevados a n é igual ao numero N, então N é um numero de Armstrong*/
            qtd++;
            /*Grava o numero de armstrong encontrado no arquivo de saida*/
            fprintf(saida,"%d\n",k);
        }


    }
    /*devolve a quantidade de numeros de armstrong encontrada*/
    return qtd;


    /*fecha os arquivos de entrada e saida, que não serao mais utilizados*/
    fclose(entrada);
    fclose(saida);
}
