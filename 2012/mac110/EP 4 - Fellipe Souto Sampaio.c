/********************************************************/
/* Fellipe Souto Sampaio                                */
/* Número USP : 7990422                                 */
/* Exercicio-Programa - Alagações na USSP EP4           */
/* Curso: Bacharelado Matemática - Turma: 2012 -        */
/* Profa. Yoshiko Wakabayashi                           */
/* Compilador: Code :: Blocks 10.05                     */
/********************************************************/


#include <stdio.h>
#include <string.h>

#define MAX_LIN 50
#define MAX_COL 50
#define TAMANHO_NOME 20
#define TRUE 1
#define FALSE 0

void cmatriz (int matriz [MAX_LIN][MAX_COL],int lin,int col, FILE *arq_entrada, FILE *arq_saida);
/*Faz a leitura do arquivo de entrada e organiza os pontos de alagamento em uma matriz MxN e imprime no arquivo de saida*/

void cria_lista (int matriz [MAX_LIN][MAX_COL],int mlista [][MAX_COL],int lin,int col);
/*Cria uma matriz de três colunas na qual guarda as coordenadas do ponto de alagamento da matriz principal*/

int ehvizinho (int x, int y, int z,int w);
/*Testa se duas posições dadas são adjacentes*/

void marcacomk (int matriz [][MAX_COL],int mlista [][MAX_COL]);
/*Recebe a matriz lista e testa a adjacencia entre as coordenadas, atribuindo números de 1 a k na terceira coluna, onde k é o máximo de regiões alagadas*/

void marcamatriz (int matriz [][MAX_COL],int mlista [][MAX_COL]);
/*Escreve de volta a matriz principal, utilizando as informações de adjacencias para separar as regiões alagadas*/

void marca_char (int matriz [][MAX_COL],int mlista [][MAX_COL]);
/*Realiza a mesma tarefa da função anterior, entretando a função soma 64 as coordenadas diferentes de zero*/

void imprime_m (int matriz [][MAX_COL], int linha, int coluna);
/*Função que imprime na tela a matriz do tipo numérica*/

void imprime_ms (int matriz [][MAX_COL], int linha, int coluna, FILE *arq_entrada, FILE *arq_saida);
/*Função que imprime no arquivo de saída a matriz do tipo numérica*/

void imprime_char (int matriz [][MAX_COL], int linha, int coluna);
/*Função que imprime na tela a matriz do tipo caracter*/

void imprime_chars (int matriz [][MAX_COL], int linha, int coluna,FILE *arq_entrada, FILE *arq_saida);
/*Função que imprime no arquivo de saída a matriz do tipo caracter*/

int main ()
{


        int lin,col;
        int matriz [MAX_LIN][MAX_COL],mlista [MAX_LIN*MAX_COL][MAX_COL];

        FILE *arq_entrada, *arq_saida;

        char nome_file_entrada [TAMANHO_NOME];
        char nome_file_saida [TAMANHO_NOME];
        printf ("*********** Programa para analise de pontos de alagamento ***********\n");


        printf ("\n\t    Digite o nome do arquivo de entrada : ");
        scanf ("%s", nome_file_entrada);

        printf ("\n\t    Digite o nome do arquivo de saida : ");
        scanf ("%s",nome_file_saida);

        printf ("\n\t    Digite a ordem da Matriz, primeiro linhas e depois colunas : ");
        scanf ("%d %d",&lin,&col);

        arq_entrada = fopen (nome_file_entrada, "r");

        arq_saida = fopen (nome_file_saida, "w");

        if (arq_entrada == NULL)
            printf ("Arquivo de entrada %s nao existe\n",nome_file_entrada);

        fprintf(arq_saida,"****************************************************************\n");
        fprintf(arq_saida,"***                                                          ***\n");
        fprintf(arq_saida,"***    MAC0110 - Introducao a Computacao - 1o. semestre 2012 ***\n");
        fprintf(arq_saida,"***    Quarto Exercício Programa (EP4)                       ***\n");
        fprintf(arq_saida,"***                                                          ***\n");
        fprintf(arq_saida,"***    Aluno : Fellipe Souto Sampaio                         ***\n");
        fprintf(arq_saida,"***    Numero USP : 7990422                                  ***\n");
        fprintf(arq_saida,"***    Curso : Bacharelado Matemática                        ***\n");
        fprintf(arq_saida,"***                                                          ***\n");
        fprintf(arq_saida,"****************************************************************\n\n\n");

        cmatriz (matriz,lin,col,&*arq_entrada,&*arq_saida);

        cria_lista (matriz,mlista,lin,col);


        marcacomk (matriz,mlista);


        printf ("\n\n\tMatriz numerica dos pontos de alagamento\n\n");
        marcamatriz (matriz,mlista);
        imprime_m(matriz,lin,col);
        imprime_ms(matriz,lin,col,&*arq_entrada,&*arq_saida);

        printf ("\n\n\tMatriz char dos pontos de alagamento\n\n");
        marca_char (matriz,mlista);
        imprime_char(matriz,lin,col);
        imprime_chars(matriz,lin,col,&*arq_entrada,&*arq_saida);








        fclose (arq_entrada);
        fclose (arq_saida);

        return 0;
}


void cmatriz (int matriz [MAX_LIN][MAX_COL],int lin,int col, FILE *arq_entrada, FILE *arq_saida)

    {
        int i, j;

        fprintf (arq_saida," Matriz Criada \n\n");
        for (i=0 ; i<lin ; i++)
        {
            for (j=0 ; j<col ; j++)
            {
                fscanf (arq_entrada,"%d",&matriz [i][j]);

                if (matriz [i][j]==-1)
                    fprintf (arq_saida, "%4d ", matriz [i][j]);


                if (matriz [i][j]==0)
                    fprintf (arq_saida, "%4d ", matriz [i][j]);
            }

            fprintf (arq_saida,"\n");
        }

         return ;


    }

void cria_lista (int matriz [MAX_COL][MAX_COL],int mlista [] [MAX_COL], int linha,int coluna) /*função ok*/

    {
        int linn,coll,linn2=0,contador = 0;


          for (linn=0 ; linn < linha ; linn++) /*Atribui as posições de Matriz para a Lista*/
            {
                for  (coll=0;coll < coluna ; coll++)
                 {
                    if (matriz [linn][coll]== -1)
                        {
                            mlista [linn2][0] = linn;
                            mlista [linn2][1] = coll;
                            mlista [linn2][2] = -99;
                            contador++;
                            linn2++;
                        }
                 }

            }

          for (linn = contador; linha*coluna-linn > 0 ; linn++) /*preenche as linhas restantes com -3 */
            {
                mlista [linn][0] = -3;
                mlista [linn][1] = -3;
                mlista [linn][2] = -3;
            }


        return ;
    }

void marcacomk (int matriz [][MAX_COL],int mlista [][MAX_COL])/*ok, poderia mudar o nome para marcalista*/

   {
        int linha,klinha,k=0,estatus;

        mlista [0][2] = 1;

                for (linha = 0; mlista [linha] [1] != -3 ; linha ++)
                {
                    if (mlista [linha][2] == -99)
                        {
                            k++;

                            if (ehvizinho(mlista [linha][0],mlista [linha][1],mlista [linha+1][0],mlista [linha+1][1]) ==  TRUE && mlista [linha+1][2] != -99)
                                k--;

                            mlista [linha] [2] = k+1;

                        }
                    for (klinha = linha+1 ; mlista [klinha][0] != -3 ; klinha ++)
                    {
                        estatus = ehvizinho(mlista [linha][0],mlista [linha][1],mlista [klinha][0],mlista [klinha][1]);

                        if (estatus == TRUE)
                         {
                             if (mlista [klinha][2] != -99)
                             {
                                mlista [linha][2] = mlista [klinha][2];
                             }
                            else
                                mlista [klinha][2] = mlista [linha][2];

                        }


                    }

                }

            return;
        }

void marcamatriz (int matriz [][MAX_COL],int mlista [][MAX_COL]) /*certinha*/

    {
        int i,m,n;

        for (i= 0;mlista [i][0] != -3; i++)
            {
                m = mlista [i][0];
                n = mlista [i][1];
                matriz [m] [n] = mlista [i][2];
            }
        return;
    }

void marca_char (int matriz [][MAX_COL],int mlista [][MAX_COL]) /*ok*/

    {
        int i,m,n;

        for (i= 0;mlista [i][0] != -3; i++)
            {
                m = mlista [i][0];
                n = mlista [i][1];
                matriz [m] [n] = mlista [i][2]+64;
            }
        return;
    }
void imprime_char (int matriz [][MAX_COL], int linha, int coluna) /*okzeão! */

    {
        int i,j;

            for (i=0; i<linha ; i++)
                {
                    for (j=0; j<coluna; j++)
                        {
                            if (matriz [i][j] == 0)
                                printf (" %4c ", matriz [i][j]+42);
                            else
                                printf (" %4c ", matriz [i][j]);
                        }

                    printf ("\n");
                }

            return;

    }

void imprime_m (int matriz [][MAX_COL], int linha, int coluna)
    {
        int i,j;

        for (i=0; i<linha ; i++)
            {
                for (j=0; j<coluna; j++)
                    printf (" %4d ", matriz [i][j]);


                printf ("\n");
            }

        return;
    }

void imprime_chars (int matriz [][MAX_COL], int linha, int coluna,FILE *arq_entrada, FILE *arq_saida) /*okzeão! */

    {
        int i,j;

            fprintf (arq_saida,"\n\n Matriz char dos pontos de alagamento \n\n");
            for (i=0; i<linha ; i++)
                {
                    for (j=0; j<coluna; j++)
                        {
                            if (matriz [i][j] == 0)
                                fprintf (arq_saida," %4c ", matriz [i][j]+42);
                            else
                                fprintf (arq_saida," %4c ", matriz [i][j]);
                        }

                    fprintf (arq_saida,"\n");
                }

            return;

    }

void imprime_ms (int matriz [][MAX_COL], int linha, int coluna,FILE *arq_entrada, FILE *arq_saida)
    {
        int i,j;

        fprintf (arq_saida," \n\nMatriz numerica dos pontos de alagamento \n\n");
        for (i=0; i<linha ; i++)
            {
                for (j=0; j<coluna; j++)
                    fprintf (arq_saida," %4d ", matriz [i][j]);


                fprintf (arq_saida,"\n");

            }

        return;
    }

int ehvizinho (int x, int y, int z,int w) /*okezs*/

    {

        int state=0;

        if ( y == w)
        {
            if (x+1 == z || x-1 == z || x == z)
                state =1;

        }

        if ( x == z)
        {
            if (y+1 == w || y-1 == w || y == w)
                state =1;


        }

       return (state);
    }
/*....................................Descrição..das..Variáveis............................................................................*/

/*..........................................Função..Main...................................................................................*/
/* lin : Armazena o número de linhas da matriz                                                                                             */
/* col : Armazena o número de colunas da matriz                                                                                            */
/* matriz : Matriz principal na qual será estudado os pontos de alagamento                                                                 */
/* mlista : Matriz similar a uma lista que salvara as coordenadas dos pontos de alagamento e o número da região alagada                    */
/* *arq_entrada : Ponteiro para manuzeio da abertura do arquivo de entrada                                                                 */
/* *arq_saida : Ponteiro para manuzeio da escrita do arquivo de saída                                                                      */
/* nome_file_entrada : Armazena o nome do arquivo de entrada                                                                               */
/* nome_file_saida : Armazena o nome do arquivo de saida                                                                                   */

/*..........................................Função..Cmatriz................................................................................*/
/* i : Variável contadora de linhas da Matriz                                                                                              */
/* j : Variável contadora de colunas da Matriz                                                                                             */


/*..........................................Função..Cria_lista.............................................................................*/
/* linn : Variável contadora de linhas da Matriz                                                                                           */
/* coll : Variável contadora de colunas da Matriz                                                                                          */
/* linn2 : Variável contadora de linhas da Mlista                                                                                          */
/* contador : Variável contadora dos pontos de alagamento totais                                                                           */

/*..........................................Função..Marcacomk..............................................................................*/
/* linha : Variavel contadora de linhas de Mlista na posição XY                                                                            */
/* klinha : Variavel contadora de linhas de Mlista na posição ZW                                                                           */
/* estatus : Variavel que quarda o estatus se duas posições são adjacentes ou não                                                          */

/*..........................................Função..Marcacomk..............................................................................*/
/* linha : Variavel contadora de linhas de Mlista na posição XY                                                                            */
/* klinha : Variavel contadora de linhas de Mlista na posição ZW                                                                           */
/* estatus : Variavel que quarda o estatus se duas posições são adjacentes ou não                                                          */
/* K : Variavel contadora das regiões de alagamento estudada                                                                               */



/*..........................................Função..Marcamatriz............................................................................*/
/* m : Recebe a coordenada X da Matriz                                                                                                     */
/* n : Recebe a coordenada Y da Matriz                                                                                                     */
/* i : Guia a posição da linha de Mlista                                                                                                   */

/*..........................................Função..Marca_char.............................................................................*/
/* m : Recebe a coordenada X da Matriz                                                                                                     */
/* n : Recebe a coordenada Y da Matriz                                                                                                     */
/* i : Guia a posição da linha de Mlista                                                                                                   */

/*..........................................Função..Imprime_char...........................................................................*/
/* i : Variável contadora de linhas da Matriz                                                                                              */
/* j : Variável contadora de colunas da Matriz                                                                                             */

/*..........................................Função..Imprime_chars..........................................................................*/
/* i : Variável contadora de linhas da Matriz                                                                                              */
/* j : Variável contadora de colunas da Matriz                                                                                             */

/*..........................................Função..Imprime_m..............................................................................*/
/* i : Variável contadora de linhas da Matriz                                                                                              */
/* j : Variável contadora de colunas da Matriz                                                                                             */

/*..........................................Função..Imprime_ms.............................................................................*/
/* i : Variável contadora de linhas da Matriz                                                                                              */
/* j : Variável contadora de colunas da Matriz                                                                                             */

/*..........................................Função..ehvizinho..............................................................................*/
/* state : Guarda o estatus da comparação entre as coordenadas XY e ZW                                                                     */
