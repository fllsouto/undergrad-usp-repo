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

  EP4.c
  Calculadora II

  Referências: Com exceção das rotinas fornecidas no esqueleto e em sala
  de aula, caso você tenha utilizado alguma refência, liste-as abaixo
  para que o seu programa não seja considerada plágio.
  Exemplo:
  - função mallocc retirada de: http://www.ime.usp.br/~pf/algoritmos/aulas/aloca.html

  Referência:
  - função criacelula foi criada baseando-se na teoria disponível em http://www.ime.usp.br/~pf/algoritmos/aulas/fila.html
  - função infixaParaPosfixa foi baseada em outra de mesmo ńome disponível em http://www.ime.usp.br/~pf/algoritmos/aulas/pilha.html

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
#define MAX_TAMANHO 200 /* de 80 o valor foi alterado para 200 em vista da posibilidade de existir diversas operações ou variáveis na expressão*/
#define TRUE 1
#define FALSE 0

/* codigos */
#define NUMERO  '#'
#define SOMA    '+'
#define SUB     '-'
#define MULT    '*'
#define DIV     '/'
#define EXP     '^'
#define NEG     '!'
#define ATR     '='


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

typedef struct {
  int inic;
  float valor;
}Tabela;



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
float calculaPosfixa(Celula *cab,Tabela variavel [26]);
float operacalc (char ,float , float);
char *infixaParaPosfixa (char inf[]);
void tabelastart (Tabela *);
void imprimetabela (Tabela*);

/*
\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
  5  M A I N

//////////////////////////////////////////////////////////////////////
*/

int main(int argc, char *argv[]){

    FILE *fentrada;
    char linha[MAX_TAMANHO],*posfix; /* recebe linha do arquivo de entrada */
    Celula *cab;
      /*Celula *elemento;*/
    Tabela variavel [26];
     /* fila de numeros e operadores */
    int i = 0;
    int contaLinha = 0;
    float numero = 0;

    tabelastart(variavel);

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


                /*Chamada das funções implementadas por mim*/

        /*Conversão da expressão infixa em posfixa*/

        posfix = infixaParaPosfixa(linha);

        /*Impressão das expressões*/

        printf("\n\nLinha : %d\n", contaLinha);
        printf("Expressao infixa : %s\n", linha);
        printf("Expressao Posfixa: %s\n", posfix);


        /*Criação da fila posfixa e cálculo da expressão*/

        cab = constroiFilaPosfixa(posfix);
        numero = calculaPosfixa(cab,variavel);

        /*Impressão do resultado*/

        printf ("Resultado : %f\n",numero);

        /*Impressão da tabela de variáveis*/

        imprimetabela(variavel);


    }

    return 0;
}

/*
/////////////////////////////////////////////////////////////////////
  6  IMPLEMENTACAO DAS FUNCOES QUE VOCE DEVE FAZER

\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
*/


/* ======================================================================

    Recebe como uma entrada uma string de expressão infixa e gera como saida
    a mesma expressão convertida em posfixa

*/
char *infixaParaPosfixa (char *linha) {

    char *strposf;
    char *pilha;
    int n = strlen (linha);
    int  k = 1;
    int i,j;

    /*Criação da nova string e da pilha para manipulação dos operadores*/
    strposf = mallocSafe(n * sizeof (char));
    pilha = mallocSafe(n * sizeof (char));

    /*Marca o fim da pilha com um @ */
    pilha[0] = '@';

    for (j = 0, i = 0; linha[i] != '\0'; ++i) {
        switch (linha[i]) {
            char x;
            case '(':
            {
                pilha[k] = linha[i];
                k++;
                break;
            }

            case ')':
            {
                strposf[j++] = ' ';
                while (1) {
                    x = pilha[--k];
                    if (x == '(')
                        break;
                    strposf[j++] = x;
                }
                break;
            }

            case '+':
            case '-':
            {
                while (1) {
                    x = pilha[k-1];
                    if (x == '(' || x == '='|| x == '@')
                        break;
                    --k;
                    strposf[j++] = x;
                }
                pilha[k] = linha[i];
                k++;
                break;
            }

            case '*':
            case '/':
            {
                while (1) {
                    x = pilha[k-1];
                    if (x == '(' || x == '+' || x == '-' || x == '=' || x == '@')
                        break;
                    --k;
                    strposf[j++] = x;
                }
                pilha[k] = linha[i];
                k++;
                break;
            }

            case '^':
            {

                while (1) {
                    x = pilha[k-1];

                    if (x == '(' || x == '+' || x == '-' || x == '/' || x == '*' || x == '^'|| x == '='|| x == '@')
                        break;
                    --k;
                    strposf[j++] = x;
                }
                pilha[k] = linha[i];
                k++;
                break;
            }

            case '!':
            {
                pilha[k] = linha[i];
                k++;
                break;
            }

            case '=':
            {
                while (1) {
                    x = pilha[k-1];
                    if (x == '('|| x == '='|| x == '@')
                        break;
                    --k;
                    strposf[j++] = x;
                }
                pilha[k] = linha[i];
                k++;
                break;
            }

            case ' ':
            {
                if (strposf [j] == ' ' && linha [i] == ' ' )
                    break;
                else{
                    strposf[j++] = linha[i];
                    break;
                }
            }
            default:{
                strposf[j++] = linha[i];
            }

      }


        /*Caso a string tenha chego ao fim e ainda exista operadores na pilha a seguinte rotina
        descarrega o conteudo da pilha direto na string posfixa seguindo a lógica FILO*/

        if (linha[i+1] == '\0'){
            char x;
            k--;
            while (1) {
                x = pilha[k];
                if (pilha[k] == '@')
                    break;
                --k;
                strposf[j++] = ' ';
                strposf[j++] = x;

            }
        }
   }


    /*Ver OBSERVAÇÕES GERAIS no final do código */
    /*free (pilha);*/
    strposf[j] = '\0';
    return strposf;
}


/* ======================================================================

    Recebe um string linha contendo a expressão infixa e devolve o
    endereço cab da célula cabeça da fila contruída.

*/
Celula *constroiFilaPosfixa (char *linha){

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
            case '=':
            {
                head = criacelula(head,*ptr,0);/*em vez de ignorar o lixo contido no campo número prefiro adotar por definição 0 no campo cel.numero*/
                break;
            }
            /*Caso em que o dado no array é do tipo número ou variável*/
            default:
            {
                if (*ptr > 64 && *ptr < 91){
                    head = criacelula(head,*ptr,0);/*em vez de ignorar o lixo contido no campo número prefiro adotar por definição 0 no campo cel.numero*/
                    break;
                }
                else{
                    number = strtof(ptr,&ptr);
                    head = criacelula(head,'#',number);
                    break;
                }

            }
        }
        ptr++;
    }

    /*Ao final da construção da lista circular optei por sinalizar a cabeça com o caracter H no campo simbolo*/
    head->simbolo = 'H';

    /*retorna para a função main o endereço da cabeça criada*/
    return head;
}


/* ======================================================================

    Função auxiliar para criação dos nós da fila, recebe a cabeça, un número ou uma operação.
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


/* ======================================================================

    Inicializa o vetor de struct do tipo tabela de acordo com as definções apresentadas
    no enunciado do problema

*/
void tabelastart (Tabela variavel[26]){

    Tabela *acertatab;
    int k = 0;

    acertatab = variavel;

    while (k < 26){
        acertatab->inic = FALSE;
        acertatab++;
        k++;
    }


}


/* ======================================================================

    Recebe uma fila circular com cabeça cab de números e operadores
    representando um expressão posfixa. Calcula o valor da expressão e
    atualiza o valor das variáveis no vetor variavel.

*/
float calculaPosfixa(Celula *cab,Tabela variavel [26]){

    Celula *headpilha,*elemento; /*Cabeça da pilha e ponteiro temporario de manipulação*/
    Celula *nova,*top,*subtop,*undertop; /*Ponteiro para o topo e para os dois níveis abaixo da pilha*/
    Tabela *acertatab; /*Ponteiro temporario para atualização do vetor tabela*/
    float temporaria,resultado = 0;
    char vtemp;

    /*Criação da cabeça da pilha*/
    headpilha = mallocSafe(sizeof(Celula));
    headpilha->prox = NULL;

    /*Ponteiro para manipulação da fila circular*/
    elemento = cab->prox;

    /*Laço para manipulação da fila e para criação da pilha de operadores*/
    while (elemento->simbolo != 'H'){

        /*Tratamento dos casos da construção da pilha, se encontrar um número ou variável
        este será empilhado, encontrando-se uma operação esta é aplicada aos dois itens mais
        altos da pilha*/
        switch (elemento->simbolo){

            case '=':
            {   /*Configuração dos ponteiros auxiliares*/
                top = headpilha->prox;
                subtop = headpilha->prox->prox;
                undertop = headpilha->prox->prox->prox;

                /*Caso topo número e subtopo variável*/
                if (top->simbolo == '#' && subtop->simbolo != '#'){

                    vtemp = subtop->simbolo;
                    acertatab = variavel;
                    acertatab = acertatab + (vtemp % 65);

                    acertatab->inic = TRUE;
                    acertatab->valor = top->numero;
                    resultado = temporaria = acertatab->valor;


                    nova = mallocSafe(sizeof(Celula));
                    nova->numero = temporaria;
                    nova->simbolo = '#';
                    nova->prox = undertop;

                    free(headpilha->prox);
                    headpilha->prox = nova;

                    break;
                }
                /*Caso topo e subtopo são variáveis*/
                if (top->simbolo != '#' && subtop->simbolo != '#'){

                    Tabela *acertatab2;
                    char vtemp2;

                    vtemp = top->simbolo;
                    acertatab = variavel;
                    acertatab = acertatab + (vtemp % 65);

                    vtemp2 = subtop->simbolo;
                    acertatab2 = variavel;
                    acertatab2 = acertatab2 + (vtemp2 % 65);

                    acertatab2->inic = TRUE;
                    acertatab2->valor = acertatab->valor;
                    resultado = temporaria = acertatab2->valor;

                    nova = mallocSafe(sizeof(Celula));
                    nova->numero = temporaria;
                    nova->simbolo = '#';
                    nova->prox = undertop;

                    free(headpilha->prox);
                    headpilha->prox = nova;

                    break;
                }

            }
            /*Empilhamento dos números*/
            case '#':
            {

                nova = mallocSafe(sizeof(Celula));
                nova->prox = headpilha->prox;
                nova->simbolo = '#';
                nova->numero = elemento->numero;
                headpilha->prox = nova;
                break;
            }
            /*Operação entre os números*/
            case '+':
            case '-':
            case '*':
            case '/':
            case '^':
            case '!':
            {
                top = headpilha->prox;

                /*Tratamento do caso no qual a operação é a troca de sinal*/
                if (elemento->simbolo == '!'){

                    if (top->simbolo == '#'){ /*Troca de sinal de um número*/
                        resultado = operacalc (elemento->simbolo,top->numero,-1);
                        top->numero = resultado;
                        break;
                    }
                    else{ /*Troca de sinal de uma variável*/
                        vtemp = top->simbolo;
                        acertatab = variavel;
                        acertatab = acertatab + (vtemp % 65);
                        resultado = operacalc (elemento->simbolo,acertatab->valor,-1);
                        acertatab->valor = resultado;
                        break;
                    }

                }
                /*Casos gerais*/
                else{

                    /*Ponteiros para melhorar a indexação*/
                    subtop = headpilha->prox->prox;
                    undertop = headpilha->prox->prox->prox;

                    /*Desempilhamento dos números operados e empilhamento do resultado*/

                    if(top->simbolo == '#' && subtop->simbolo == '#'){ /*Caso topo pilha número e subtopo número*/

                        resultado = operacalc (elemento->simbolo,top->numero,subtop->numero);

                        nova = mallocSafe(sizeof(Celula));
                        nova->numero = resultado;
                        nova->simbolo = '#';
                        nova->prox = undertop;
                        free(headpilha->prox);
                        headpilha->prox = nova;
                        break;
                    }
                    if(top->simbolo == '#' && subtop->simbolo != '#'){ /*Caso topo pilha número e subtopo variavel*/

                        /*Utiliza o resto da divisão do valor da variavel
                        em decimal ASCII por 65 para indexação do vetor variavel*/

                        vtemp = subtop->simbolo;
                        acertatab = variavel;
                        acertatab = acertatab + (vtemp % 65);
                        resultado = operacalc (elemento->simbolo,top->numero,acertatab->valor);

                        nova = mallocSafe(sizeof(Celula));
                        nova->numero = resultado;
                        nova->simbolo = '#';
                        nova->prox = undertop;
                        free(headpilha->prox);
                        headpilha->prox = nova;
                        break;
                    }
                    if(top->simbolo != '#' && subtop->simbolo == '#'){ /*Caso topo pilha variável e subtopo número*/


                        vtemp = top->simbolo;
                        acertatab = variavel;
                        acertatab = acertatab + (vtemp % 65);
                        resultado = operacalc (elemento->simbolo,acertatab->valor,subtop->numero);

                        nova = mallocSafe(sizeof(Celula));
                        nova->numero = resultado;
                        nova->simbolo = '#';
                        nova->prox = undertop;
                        free(headpilha->prox);
                        headpilha->prox = nova;
                        break;
                    }
                    if(top->simbolo != '#' && subtop->simbolo != '#'){ /*Caso topo pilha variável e subtopo variável*/

                        Tabela *acertatab2;
                        char vtemp2;

                        vtemp = top->simbolo;
                        acertatab = variavel;
                        acertatab = acertatab + (vtemp % 65);

                        vtemp2 = subtop->simbolo;
                        acertatab2 = variavel;
                        acertatab2 = acertatab2 + (vtemp2 % 65);

                        resultado = operacalc (elemento->simbolo,acertatab->valor,acertatab2->valor);

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

            default : /*empilhamento dos números e variáveis*/
            {
                nova = mallocSafe(sizeof(Celula));
                nova->prox = headpilha->prox;
                nova->simbolo = elemento->simbolo;
                nova->numero = elemento->numero;
                headpilha->prox = nova;
                break;
            }

        }
        elemento = elemento->prox;

    }


  /*Retorna o resultado da expressão com a tabela de variáveis atualizada*/
  return resultado;
}

/* ======================================================================

    Função auxiliar que realiza as operações aritméticas entre os números e
    retorna o resultado.

*/
float operacalc (char opera,float num1, float num2){

    float resultado = 0;

    switch (opera)
    {
        case '+':
        {
            resultado = num2 + num1;
            return resultado;
        }
         case '-':
        {
            resultado = num2 - num1;
            return resultado;
        }
         case '*':
        {
            resultado = num2 * num1;
            return resultado;
        }
         case '/':
        {
            resultado = num2 /  num1;
            return resultado;
        }
         case '^':
        {
            resultado = pow (num2,num1);
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


/* ======================================================================

    Função para impressão da tabela de variáveis utilizadas durante o cálculo
    das expressões.

*/
void imprimetabela (Tabela variavel [26]){

    int k=0;

    printf ("\tConteudo das variaveis:\n");
    printf ("    Variavel    |\tValor\n");
    printf ("----------------|----------------\n");
    while(k<26){
        if(variavel[k].inic == TRUE)
            printf ("\t%c\t|\t%f\t\n",65+k,variavel[k].valor);
        k++;

    }
    printf ("...................................................................\n\n");

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




/*
\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
    OBSERVAÇÕES GERAIS

//////////////////////////////////////////////////////////////////////
*/
/*  Ao construir a função infixaParaPosfixa me deparei com o seguinte
erro no quarto exemplo de entrada:

*** glibc detected *** ./zetasource: double free or corruption (out): 0x08221350 ***

Consultei o monitor Andrew e tentamos depurar o erro mas não conseguimos. A unica forma
de prevenir que o erro não ocorra é desabilitando o comando free(pilha) no final da função.
Acredito que o intuito do exercício programa não seja criar um programa profissional que realiza
extensos cálculos infixos e sim levar o aluno à prática da programação, do raciocínio lógico e dos
conceitos abordados em sala de aula. Seguindo este raciocínio, que julgo ser totalmente de acordo com
o ambiente de aprendizado que estou inserido, prefiro por desabilitar a função free ao fim da minha
função, isso não prejudicou em nada o cálculo das outras expressões e também não sobrecarregou a memória
do computador. Foi o unico meio que encontrei para que meu programa execute a tarefa apresentada no enunciado
do problema.

Sem mais,

Fellipe Souto Sampaio (Matemática Pura).

*/
