/***************************************************************/
/**                                                           **/
/**   Caio Lopes Demario          N�mero USP: 7991187         **/
/**   Fellipe Souto Sampaio       N�mero USP: 7990422         **/
/**   Exerc�cio-Programa 01       MAC0211                     **/
/**                                                           **/
/**   Professora Kelly Rosa Braghetto                         **/
/***************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define maxName 100

int main (int argc, char* argv[]){

    /*variavel para o nome do arquivo .txt que ser� gerado com numeros aleatorios */
    char *aleatorio;
    /*variavel para o nome do arquivo .txt que ser� gerado com numeros sequenciais */
    char *sequencial;
    /*arquivos onde ser�o salvos os valores aleatorios e sequenciais*/
    FILE *ale, *seq;
    /*quantidade de numeros a serem gerados*/
    int tam = 0;
    /*contadores*/
    int i,linha;
    /*semente do gerador de numeros aleatorios*/
    int seed;


    aleatorio = argv[1];
    sequencial = argv[2];

    /*entrada da quantidade de numeros*/
    printf ("Informe a quantidade de numeros a serem gerados : ");
    scanf ("%d", &tam);

    printf ("\n Quantidade de numeros a ser gerada : %d\n",tam);
    /*entrada da semente do gerador*/
    printf("\nForneca uma semente inteira para sequencia : ");
    scanf ("%d", &seed);

    /*abre o arquivo com o nome guardado na vari�vel 'sequencial' para escrita e guarda na variavel de arquivo 'seq'*/
    seq = fopen(sequencial, "w");

    if (seq == NULL) {
        printf("\nNao foi possivel criar o arquivo %s.\n\n", sequencial);
        exit(-1);
    }

    /*la�o que gera n�meros sequenciais e grava no arquivo que est� em 'seq' */
    for (i = 0, linha = 0; i < tam; i++, linha++){

        fprintf(seq,"%d ",i);
        if (linha == 100){
            fprintf(seq,"\n");
            linha = 0;
        }
    }
    /*fecha o arquivo*/
    fclose(seq);

    /*abre o arquivo com o nome guardado na vari�vel 'aleatorio' para escrita, e guarda na variavel de arquivo 'ale'*/
    ale = fopen(aleatorio, "w");
    if (seq == NULL) {
        printf("\nNao foi possivel criar o arquivo %s.\n\n", aleatorio);
        exit(-1);
    }

    /*la�o que gera n�meros aleatorios e grava no arquivo que est� em 'ale' */
    for (i = 0, linha = 0; i < tam; i++, linha++){

        fprintf(ale,"%d ",rand());
        /*para cada 100 numeros, uma quebra de linha*/
        if (linha == 100){
            fprintf(ale,"\n");
            linha = 0;
        }
        if(linha == 1000)
            srand(rand());
    }
    /*fecha o arquivo*/
    fclose(ale);


    return 0;

}
