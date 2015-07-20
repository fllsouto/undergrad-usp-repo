/********************************************************/
/* Fellipe Souto Sampaio                                */
/* N�mero USP : 7990422                                 */
/* Exercicio-Programa - Alaga��es na USSP EP4           */
/* Curso: Bacharelado Matem�tica - Turma: 2012 -        */
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
/*Cria uma matriz de tr�s colunas na qual guarda as coordenadas do ponto de alagamento da matriz principal*/

int ehvizinho (int x, int y, int z,int w);
/*Testa se duas posi��es dadas s�o adjacentes*/

void marcacomk (int matriz [][MAX_COL],int mlista [][MAX_COL]);
/*Recebe a matriz lista e testa a adjacencia entre as coordenadas, atribuindo n�meros de 1 a k na terceira coluna, onde k � o m�ximo de regi�es alagadas*/

void marcamatriz (int matriz [][MAX_COL],int mlista [][MAX_COL]);
/*Escreve de volta a matriz principal, utilizando as informa��es de adjacencias para separar as regi�es alagadas*/

void marca_char (int matriz [][MAX_COL],int mlista [][MAX_COL]);
/*Realiza a mesma tarefa da fun��o anterior, entretando a fun��o soma 64 as coordenadas diferentes de zero*/

void imprime_m (int matriz [][MAX_COL], int linha, int coluna);
/*Fun��o que imprime na tela a matriz do tipo num�rica*/

void imprime_ms (int matriz [][MAX_COL], int linha, int coluna, FILE *arq_entrada, FILE *arq_saida);
/*Fun��o que imprime no arquivo de sa�da a matriz do tipo num�rica*/

void imprime_char (int matriz [][MAX_COL], int linha, int coluna);
/*Fun��o que imprime na tela a matriz do tipo caracter*/

void imprime_chars (int matriz [][MAX_COL], int linha, int coluna,FILE *arq_entrada, FILE *arq_saida);
/*Fun��o que imprime no arquivo de sa�da a matriz do tipo caracter*/

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
        fprintf(arq_saida,"***    Quarto Exerc�cio Programa (EP4)                       ***\n");
        fprintf(arq_saida,"***                                                          ***\n");
        fprintf(arq_saida,"***    Aluno : Fellipe Souto Sampaio                         ***\n");
        fprintf(arq_saida,"***    Numero USP : 7990422                                  ***\n");
        fprintf(arq_saida,"***    Curso : Bacharelado Matem�tica                        ***\n");
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

void cria_lista (int matriz [MAX_COL][MAX_COL],int mlista [] [MAX_COL], int linha,int coluna) /*fun��o ok*/

    {
        int linn,coll,linn2=0,contador = 0;


          for (linn=0 ; linn < linha ; linn++) /*Atribui as posi��es de Matriz para a Lista*/
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
void imprime_char (int matriz [][MAX_COL], int linha, int coluna) /*okze�o! */

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

void imprime_chars (int matriz [][MAX_COL], int linha, int coluna,FILE *arq_entrada, FILE *arq_saida) /*okze�o! */

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
/*....................................Descri��o..das..Vari�veis............................................................................*/

/*..........................................Fun��o..Main...................................................................................*/
/* lin : Armazena o n�mero de linhas da matriz                                                                                             */
/* col : Armazena o n�mero de colunas da matriz                                                                                            */
/* matriz : Matriz principal na qual ser� estudado os pontos de alagamento                                                                 */
/* mlista : Matriz similar a uma lista que salvara as coordenadas dos pontos de alagamento e o n�mero da regi�o alagada                    */
/* *arq_entrada : Ponteiro para manuzeio da abertura do arquivo de entrada                                                                 */
/* *arq_saida : Ponteiro para manuzeio da escrita do arquivo de sa�da                                                                      */
/* nome_file_entrada : Armazena o nome do arquivo de entrada                                                                               */
/* nome_file_saida : Armazena o nome do arquivo de saida                                                                                   */

/*..........................................Fun��o..Cmatriz................................................................................*/
/* i : Vari�vel contadora de linhas da Matriz                                                                                              */
/* j : Vari�vel contadora de colunas da Matriz                                                                                             */


/*..........................................Fun��o..Cria_lista.............................................................................*/
/* linn : Vari�vel contadora de linhas da Matriz                                                                                           */
/* coll : Vari�vel contadora de colunas da Matriz                                                                                          */
/* linn2 : Vari�vel contadora de linhas da Mlista                                                                                          */
/* contador : Vari�vel contadora dos pontos de alagamento totais                                                                           */

/*..........................................Fun��o..Marcacomk..............................................................................*/
/* linha : Variavel contadora de linhas de Mlista na posi��o XY                                                                            */
/* klinha : Variavel contadora de linhas de Mlista na posi��o ZW                                                                           */
/* estatus : Variavel que quarda o estatus se duas posi��es s�o adjacentes ou n�o                                                          */

/*..........................................Fun��o..Marcacomk..............................................................................*/
/* linha : Variavel contadora de linhas de Mlista na posi��o XY                                                                            */
/* klinha : Variavel contadora de linhas de Mlista na posi��o ZW                                                                           */
/* estatus : Variavel que quarda o estatus se duas posi��es s�o adjacentes ou n�o                                                          */
/* K : Variavel contadora das regi�es de alagamento estudada                                                                               */



/*..........................................Fun��o..Marcamatriz............................................................................*/
/* m : Recebe a coordenada X da Matriz                                                                                                     */
/* n : Recebe a coordenada Y da Matriz                                                                                                     */
/* i : Guia a posi��o da linha de Mlista                                                                                                   */

/*..........................................Fun��o..Marca_char.............................................................................*/
/* m : Recebe a coordenada X da Matriz                                                                                                     */
/* n : Recebe a coordenada Y da Matriz                                                                                                     */
/* i : Guia a posi��o da linha de Mlista                                                                                                   */

/*..........................................Fun��o..Imprime_char...........................................................................*/
/* i : Vari�vel contadora de linhas da Matriz                                                                                              */
/* j : Vari�vel contadora de colunas da Matriz                                                                                             */

/*..........................................Fun��o..Imprime_chars..........................................................................*/
/* i : Vari�vel contadora de linhas da Matriz                                                                                              */
/* j : Vari�vel contadora de colunas da Matriz                                                                                             */

/*..........................................Fun��o..Imprime_m..............................................................................*/
/* i : Vari�vel contadora de linhas da Matriz                                                                                              */
/* j : Vari�vel contadora de colunas da Matriz                                                                                             */

/*..........................................Fun��o..Imprime_ms.............................................................................*/
/* i : Vari�vel contadora de linhas da Matriz                                                                                              */
/* j : Vari�vel contadora de colunas da Matriz                                                                                             */

/*..........................................Fun��o..ehvizinho..............................................................................*/
/* state : Guarda o estatus da compara��o entre as coordenadas XY e ZW                                                                     */
