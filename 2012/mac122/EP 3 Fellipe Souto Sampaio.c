/*
 \__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__

  AO PREENCHER ESSE CABEÇALHO COM O MEU NOME E O MEU NÚMERO USP,
  DECLARO QUE SOU O ÚNICO AUTOR E RESPONSÁVEL POR ESSE PROGRAMA.
  TODAS AS PARTES ORIGINAIS DESSE EXERCÍCIO PROGRAMA (EP) FORAM
  DESENVOLVIDAS E IMPLEMENTADAS POR MIM SEGUINDO AS INSTRUÇÕES DESSE EP
  E QUE PORTANTO NÃO CONSTITUEM PLÁGIO. DECLARO TAMBÉM QUE SOU RESPONSÁVEL
  POR TODAS AS CÓPIAS DESSE PROGRAMA E QUE EU NÃO DISTRIBUI OU FACILITEI A
  SUA DISTRIBUIÇÃO. ESTOU CIENTE QUE OS CASOS DE PLÁGIO SÃO PUNIDOS COM
  REPROVAÇÃO DIRETA NA DISCIPLINA.

  Nome: Fellipe Souto Sampaio
  NUSP: 7990422
  Prof: Roberto Marcondes

  EP3.c
  Calculadora I

  Referências: Com exceção das rotinas fornecidas no esqueleto e em sala
  de aula, caso você tenha utilizado alguma refência, liste-as abaixo
  para que o seu programa não seja considerada plágio.
  Exemplo:
  - função mallocc retirada de: http://www.ime.usp.br/~pf/algoritmos/aulas/aloca.html

  Referência:
  - função criacelula foi criada baseando-se na teoria disponível em http://www.ime.usp.br/~pf/algoritmos/aulas/fila.html

 \__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__
*/

/*
  NAO EDITE OU MODIFIQUE NADA QUE ESTA ESCRITO NESTE ESQUELETO

  A estrutura deste esqueleto esta a seguir.
  Não altere esta estrutura.

  1  MACROS E CONSTANTES
  2  DECLARACAO DE STRUCTS e TIPOS
  3  PROTOTIPOS DAS FUNCOES DADAS
  4  PROTOTIPOS DE FUNCOES QUE VOCE DEVE FAZER
  5  M A I N
  6  IMPLEMENTACAO DAS FUNCOES QUE VOCE DEVE FAZER
  7  IMPLEMENTACAO DAS FUNCOES DADAS

  As partes deste EP que você deverá escrever são:

  5  M A I N
  6  IMPLEMENTACAO DAS FUNCOES QUE VOCE DEVE FAZER
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


/*
//////////////////////////////////////////////////////////////////////
  1  MACROS E CONSTANTES

\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
*/

/* numero maximo de caracteres em um linha */
#define MAX_TAMANHO 80

/* codigos */
#define NUMERO  '#'
#define SOMA    '+'
#define SUB     '-'
#define MULT    '*'
#define DIV     '/'
#define EXP     '^'
#define NEG     '!'

/*
//////////////////////////////////////////////////////////////////////
  2  DECLARACAO DE STRUCTS e TIPOS

\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
*/

/* ====================================================================== */
/*    Elemento para Fila e Pilha para armazenar numeros e/ou simbolos     */
/* ====================================================================== */
typedef struct celula {
  char  simbolo;
  float numero;
  struct celula *prox;
} Celula;


/*
//////////////////////////////////////////////////////////////////////
  3  PROTOTIPOS DAS FUNCOES DADAS que você não precisa implementar

\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
*/

void  * mallocSafe (size_t n);
float strtof(const char *nptr, char **endptr); /* para evitar warning */

/*
//////////////////////////////////////////////////////////////////////
  4  PROTOTIPOS DE FUNCOES QUE VOCE DEVE FAZER

\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
*/


Celula * constroiFilaPosfixa (char *linha);
Celula *criacelula (Celula *head, char simbolo, float numero);
float calculaPosfixa(Celula *cab);
float operacalc (char ,float , float);

/*
\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
  5  M A I N

//////////////////////////////////////////////////////////////////////
*/

int main(int argc, char *argv[])
{
  FILE *fentrada;
  char linha[MAX_TAMANHO]; /* recebe linha do arquivo de entrada */

  Celula *cab; /* fila de numeros e operadores */
  int i;
  int contaLinha = 0;
  float numero;

  if (argc != 2) {
    printf("Para usar digite: %s <arquivoEntrada>\n", argv[0]);
    exit(-1);
  }

  fentrada = fopen(argv[1], "r");
  if (fentrada == NULL) {
    printf("Nao consegui abrir o arquivo %s\n", argv[1]);
    exit(-1);
  }

  while ( fgets(linha, MAX_TAMANHO, fentrada) != NULL ) {
    contaLinha++;
    i = strlen(linha);

    if (i == 0) {
      printf("Linha %d: vazia \n", contaLinha);
      continue;
    }

    linha[i-1] = '\0'; /* substitui \n for fim do string */
    printf("Linha %d: %s\n", contaLinha, linha);

    /*Chamada das funções implementadas por mim*/

    cab = constroiFilaPosfixa(linha);
    numero = calculaPosfixa(cab);

    printf ("Resultado : %f\n\n",numero);


  }

  return 0;
}

/*
//////////////////////////////////////////////////////////////////////
  6  IMPLEMENTACAO DAS FUNCOES QUE VOCE DEVE FAZER

\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
*/

/* ======================================================================

  Recebe um string linha contendo a expressão posfixa e devolve o
  endereço cab da célula cabeça da fila contruída.

*/

Celula *constroiFilaPosfixa (char *linha)
{
  Celula *head;
  float number;
  char *ptr = linha;

  /*Criação da cabeça da lista circular*/
  head = mallocSafe(sizeof(Celula));
  head->prox = head;

  /*Manipulação do array de entrada para criação da fila de número e operações*/
  while (*ptr != '\0'){


        switch (*ptr)
            {
                /*Casos em que o dado no array é do tipo operação*/
                case ' ':
                    break;

                case '+':
                case '-':
                case '*':
                case '/':
                case '^':
                case '!':
                {
                    head = criacelula(head,*ptr,0);/*em vez de ignorar o lixo contido no campo número prefiro adotar por definição 0*/


                    break;
                }
                /*Caso em que o dado no array é do tipo número*/
                default:
                {
                    number = strtof(ptr,&ptr);
                    head = criacelula(head,'#',number);
                    break;

                }
            }
        ptr++;
    }
    head->simbolo = 'H';/*Ao fim da construção da lista circular optei por sinalizar a cabeça com o caracter H no campo simbolo*/

    /*retorna para a função main o endereço da cabeça criada*/
    return head;
}

/*Função auxiliar para criação dos nós da fila, recebe a cabeça, un número ou uma operação.
  Após o nó ser criado ele passa a ser a nova cabeça enquanto antiga recebe os parãmetros de
  entrada, depois disto os ponteiros são organizados e a função devolve o endereço da nova
  cabeça.

*/
Celula *criacelula (Celula *head, char simbolo, float numero){

        Celula *nova;

        nova = mallocSafe(sizeof(Celula));
        nova->prox = head->prox;
        head->prox = nova;
        head->numero = numero;
        head->simbolo = simbolo;

        return nova;
}

/* ====================================================================== */
/*
  Recebe uma fila circular com cabeça cab de números e operadores
  representando um expressão posfixa e calcula e devolve o valor da
  expressão.

 */

float calculaPosfixa(Celula *cab){

    Celula *headpilha,*elemento,*nova,*top,*subtop,*undertop;
    float resultado = 0;

    /*Criação da cabeça da pilha*/
    headpilha = mallocSafe(sizeof(Celula));
    headpilha->prox = NULL;

    /*Ponteiro para manipulação da fila circular*/
    elemento = cab->prox;

    /*Laço para manipulação da fila e para criação da pilha de operadores*/
    while (elemento->simbolo != 'H'){

        /*Tratamento dos casos da construção da pilha, se encontrar um número este será empilhado,
        encontrando-se uma operação esta é aplicada aos dois itens mais altos da pilha*/
        switch (elemento->simbolo){

            case '#':
            {
                /*Empilhamento dos números*/
                nova = mallocSafe(sizeof(Celula));
                nova->prox = headpilha->prox;
                nova->simbolo = '#';
                nova->numero = elemento->numero;
                headpilha->prox = nova;
                break;
            }
            default:
            {
                                /*Operação entre os números*/
                /*Manipulação de ponteiros para fácil indexação na função operacalc*/
                top = headpilha->prox;

                /*Tratamento do caso no qual a operação é a troca de sinal*/
                if (elemento->simbolo == '!'){

                    resultado = operacalc (elemento->simbolo,top->numero,-1);
                    top->numero = resultado;
                    break;

                }
                /*Casos gerais*/
                else{

                    /*Ponteiros para melhorar a indexação*/
                    subtop = headpilha->prox->prox;
                    undertop = headpilha->prox->prox->prox;

                    resultado = operacalc (elemento->simbolo,subtop->numero,top->numero);

                    /*Desempilhamento dos números operados e empilhamento do resultado*/
                    nova = mallocSafe(sizeof(Celula));
                    nova->numero = resultado;
                    nova->simbolo = '#';
                    nova->prox = undertop;
                    free(headpilha->prox);
                    headpilha->prox = nova;

                    break;
                }
            }







        }

        elemento = elemento->prox;

    }


  /*Retorna o resultado da operação*/
  return resultado;
}

/*Função auxiliar que realiza as operações aritméticas entre os números e retorna o resultado*/
float operacalc (char opera,float num1, float num2){

    float resultado = 0;

    switch (opera)
    {
        case '+':
        {
            resultado = num1 + num2;
            return resultado;
        }
         case '-':
        {
            resultado = num1 - num2;
            return resultado;
        }
         case '*':
        {
            resultado = num1 * num2;
            return resultado;
        }
         case '/':
        {
            resultado = num1 /  num2;
            return resultado;
        }
         case '^':
        {
            resultado = pow (num1,num2);
            return resultado;
        }
         case '!':
        {
            resultado = num1*num2;
            return resultado;
        }


    }
    return resultado;
    /*na compilação do programa na pagina do PACA ele estava dizendo que a função não retornava valor, porém
    de qualquer forma ela terá que entrar em algum dos casos acima, coloquei o return apenas para prevenir que não
    ocorra warning, entranto não seria realmente necessário.*/

}


/*
\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
  7  IMPLEMENTACAO DAS FUNCOES DADAS

//////////////////////////////////////////////////////////////////////
*/

/*
  mallocSafe: testa o ponteiro devolvido por malloc
 */
void * mallocSafe (size_t n)
{
  void * pt;
  pt = malloc(n);
  if (pt == NULL) {
    printf("ERRO na alocacao de memoria.\n");
    exit(-1);
  }
  return pt;
}


