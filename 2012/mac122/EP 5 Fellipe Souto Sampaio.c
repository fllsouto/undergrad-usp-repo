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

  EP5.c
  Ordenação de filmes

  Referências: Com exceção das rotinas fornecidas no esqueleto e em sala
  de aula, caso você tenha utilizado alguma refência, liste-as abaixo
  para que o seu programa não seja considerada plágio.
  Exemplo:
  - função mallocc retirada de: http://www.ime.usp.br/~pf/algoritmos/aulas/aloca.html

  Referências:
  -Funçao split_list foi baseada na ideia da função separa disponível em http://www.ime.usp.br/~pf/algoritmos/aulas/quick.html
  -Função ordenaporNota foi baseada na ideia algoritmo quicksort disponível em http://www.ime.usp.br/~pf/algoritmos/aulas/quick.html
  -Função searchWord foi baseada na ideia do algoritmo trivial disponível em http://www.ime.usp.br/~pf/algoritmos/aulas/strma.html
  -Função strcmp da biblioteca padrão string.h

 \__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__
*/

/*
//////////////////////////////////////////////////////////////////////

  A estrutura deste esqueleto esta a seguir.
  Não altere esta estrutura.

  1  MACROS E CONSTANTES
  2  DECLARACAO DE STRUCTS e TIPOS
  3  PROTOTIPOS DAS FUNCOES
  4  M A I N
  5  IMPLEMENTACAO DAS FUNCOES QUE VOCE DEVE FAZER
  6  IMPLEMENTACAO DAS FUNCOES QUE VOCE DESEJAR FAZER
  7  IMPLEMENTACAO DAS FUNCOES DADAS

//////////////////////////////////////////////////////////////////////
*/

#include <stdio.h>
#include <stdlib.h>    /* funcoes exit e malloc */
#include <string.h>    /* funcoes strspn e strncpy */
#include <ctype.h>     /* funcao  isdigit */

/*
//////////////////////////////////////////////////////////////////////
  1  MACROS E CONSTANTES

\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
*/

/* maior linha dos arquivos de entrada tem uns 240 caracteres */
#define TAMLINHA 300

/* numero maximo de caracteres no nome do filme */
#define TAMNOME   80

#define TRUE  1
#define FALSE 0

#define CARREGAR   'c'
#define GRAVAR     'g'
#define INSERIR    'i'
#define MOSTRAR    'm'
#define ORDENAR    'o'
#define PROCURAR   'p'
#define REMOVER    'r'
#define MSTRMENOR  't'
#define MSTRMAIOR  'u'
#define SAIR       'x'


/*
//////////////////////////////////////////////////////////////////////
  2  DECLARACAO DE STRUCTS e TIPOS

\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
*/

typedef struct filme {
  char  dist[11];
  int   votos;
  float nota;
  char  nome[TAMNOME+1];
  int   ano;
  struct filme *prox;
  struct filme *ant;
} Filme;

typedef struct lista {
  Filme *ini;
  Filme *fim;
} Lista;

/*
//////////////////////////////////////////////////////////////////////
  3  PROTOTIPOS DAS FUNCOES dadas e/ou que voce precisa implementar

  VOCE pode incluir outras funcoes se desejar.

\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
*/


/*
 * 3.1 PROTOTIPOS DAS FUNCOES QUE VOCE DEVE IMPLEMENTAR
 */
int  achaFilme(Lista *lista, Filme *f);
void quickSort(Lista *lista);
int  achaPalavra(unsigned char *pal, int tPal,
		 unsigned char *texto, int tTexto);

/*
 * 3.2 COLOQUE A SEGUIR OS PROTOTIPOS DAS OUTRAS FUNCOES QUE
 *     VOCE DESEJAR IMPLEMENTAR
 */
 int split_list (Lista *lista,int p,int r);
 Filme *acertaPonteiro (Lista *lista,int pos);
 void inserenovoFilme(Lista *lista);
 void ordenaporNota (Lista *lista,int begg,int endd);
 void trocaPos(Lista *lista,Filme *f,Filme *g);
 void mostraMenor(Lista *lista);
 void mostraMaior(Lista *lista);
 void searchWord(Lista *lista);
 void removeFilme(Lista *lista);
 void quickErase(Lista *lista,Filme *f);

/*
 * 3.3 PROTOTIPOS DAS FUNCOES DADAS
 */
void *mallocSafe(size_t n);
void  erroLeitura(char *msg, char *lin);
int   leString(char str[], int max);
char  leOpcao();

Lista *criaLista();
char  *rIndex(char *pal, char letra);
void   carregaLista(Lista *lista);
void   gravaLista(Lista *lista);

Filme *criaFilme(char *d, int v, float n, char *nm, int a);
void   insereFilme(Lista *lista, Filme *entrada);
void   mostraUmFilme(Filme *f);
void   mostraLista(Lista *lista);

/*
\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

  4  M A I N

//////////////////////////////////////////////////////////////////////
*/
int main()
{
  char opcao;
  Lista *lista = criaLista();
  int ordenado = FALSE;

  /* declaracao das demais variaveis do main */

  /* iterara ate o usuario digitar 'x' para sair */
  do {

    opcao = leOpcao();
    switch (opcao) {

    case CARREGAR:
      carregaLista(lista);
      break;

    case GRAVAR:
      gravaLista(lista);
      break;

    case INSERIR:
      inserenovoFilme(lista);
      break;

    case ORDENAR:
        quickSort(lista);
        ordenado = TRUE;
        break;

    case MOSTRAR:
      mostraLista(lista);
      break;

    case PROCURAR:
        searchWord(lista);
        break;

    case REMOVER:
        removeFilme(lista);
        break;

    case MSTRMENOR:
        if (ordenado == FALSE){
            printf ("\nLista nao ordenada, por favor ordene primeiro a lista de filmes!\n");
            break;
        }
        mostraMenor(lista);
        break;

    case MSTRMAIOR:
        if (ordenado == FALSE){
            printf ("\nLista nao ordenada, por favor ordene primeiro a lista de filmes!\n");
            break;
        }
        mostraMaior(lista);
        break;

    case SAIR:
      break;

    default :
      printf("\nOpcao '%c' nao reconhecida\n\n", opcao);
      break;
    }
  } while (opcao != SAIR);

  return 0;
}

/*
\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

  5  IMPLEMENTACAO DAS FUNCOES QUE VOCE DEVE FAZER

//////////////////////////////////////////////////////////////////////
*/

/*
----------------------------------------------------------------------
Funcao quickSort(Lista *l)
  Ordena a lista em ordem decrescente de nota utilizando o
  algoritmo Quicksort adaptado para listas encadeadas.
*/
void quickSort(Lista *lista){ /*ok*/
    Filme *f,*g;
    int contador = 1;

    g = f = lista->ini;

    while (g->prox != NULL){
        contador++;
        g = g->prox;
    }

    ordenaporNota (lista,1,contador);

}

/*
----------------------------------------------------------------------
Funcao achaFilme
  Devolve TRUE se o filme f ja esta na lista e
  devolve FALSE em caso contrario.
*/
int achaFilme(Lista *lista, Filme *f){ /*ok*/
    Filme *elemento,*new_movie;

    new_movie = f;
    elemento = lista->ini;

    while (elemento!= NULL){

        /*Compara se a string 1 é igual a string 2, se os anos anos de lançamento e as notas são iguais*/
        if (strcmp(elemento->nome,new_movie->nome) == 0 &&
            elemento->ano==new_movie->ano && elemento->nota==new_movie->nota){
            return 1;
        }
        else
            elemento = elemento->prox;
    }
    return 0;
}

/*
----------------------------------------------------------------------
Funcao achaPalavra
  Devolve TRUE quando acha a 1a ocorrencia e
  devolve FALSE em caso contrario.
*/
int  achaPalavra(unsigned char *pal, int tPal, unsigned char *texto, int tTex){ /*ok*/

    int i = 0,j=0;
    int k = 0;

    /*Passeia pelo texto da esquerda para a direita procurando a primeira ocorrência da primeira letra da palavra *pal e
      caso encontre a letra inicia uma sequência de comparações com as letras seguintes da palavra com o texto. Se todas
      as letras da palavra casarem com a do texto isso significa uma primeira ocorrência da palavra no texto e a função
      retorna TRUE*/
    for (k=0; k < tTex; k++){
        i = 0;
        j = k;

        if (pal[i] == texto[j]){
            j = k;

            while(pal[i] == texto[j]){
                i++;
                j++;

                if (i == tPal)
                    return TRUE;
            }
        }

    }
    /*Retorna FALSE caso a palavra procurada não esteja presente em nenhuma parte do texto*/
  return FALSE;
}

/*
\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

  6  IMPLEMENTACAO DAS FUNCOES QUE VOCE DESEJAR FAZER

//////////////////////////////////////////////////////////////////////
*/


/*
----------------------------------------------------------------------
Funcao inserenovoFilme
  Le através do teclado os dados fornecidos pelo usuário e cria um novo
  registro de filme.
*/
 void inserenovoFilme(Lista *lista){ /*ok*/

    float nota;
    int ano;
    int votos;
    char dist[11];
    char nome[TAMNOME+1];
    Filme *f;

    getchar(); /*Comando para limpar o Buffer do teclado*/

    printf ("\nDigite o nome do filme : ");
    fgets(nome, sizeof(nome),stdin);
    nome[strlen(nome+1)] = '\0';

    printf ("Digite o ano : ");
    scanf ("%d",&ano);
    printf ("Digite a nota : ");
    scanf ("%f",&nota);
    printf ("Digite o numero de votos : ");
    scanf ("%d",&votos);

    getchar();

    printf ("Digite a distribuicao : ");
    fgets(dist, sizeof(dist),stdin);
    dist[10] = '\0';

    printf ("\nFilme inserido : \n");
    f = criaFilme(dist, votos, nota, nome, ano);
    insereFilme(lista, f );
    mostraUmFilme(f);

 }


/*
----------------------------------------------------------------------
Funcao ordenaporNota
  Realiza a função do algoritmo recursivo Quicksort.
*/
 void ordenaporNota (Lista *lista,int begg,int endd){ /*ok*/

    int pivo = 0;
    if (begg < endd){

        pivo = split_list (lista,begg,endd);
        ordenaporNota (lista,begg,pivo-1);
        ordenaporNota (lista,pivo+1,endd);
    }

 }


/*
----------------------------------------------------------------------
Funcao split_list
  Recebe uma lista linear duplamente encadeada, seu elemento considerado como primeiro e a quantidade de registros.
  Pega como pivot o valor da nota do ultimo elemento da lista e permuta os registros de modo que no final da função
  a lista esteja com a seguinte configuração:

  NotaReg_p >= NotaReg_p+1 >= ... NotaReg_pivot-1 >= NotaReg_pivot >= NotaReg_pivot+1 ... NotaReg_r-1 >= NotaReg_r

  Ordenando a lista com os elementos maiores que o pivot a esquerda e os menores a direita e devolve como valor a ordinalidade
  do pivot dentro da lista duplamente encadeada.
  OBS: Os elemento a direita ou a esquerda não são necessáriamente menores, maiores ou iguais entre sí, eles são apenas
  em relação ao pivot.
*/
int split_list (Lista *lista,int p,int r){ /*ok*/

    int index1,index2;
    Filme *f,*g,*pivot;
    float nota1,nota2,notatemp;

    index1 = p;
    index2 = r-1;
    pivot = acertaPonteiro(lista,r);
    f = acertaPonteiro(lista,index1);
    g = acertaPonteiro(lista,index2);

    notatemp = pivot->nota;
    while (index1 <= index2){
        nota1 = f->nota;
        nota2 = g->nota;
        if (nota2 <= notatemp){
            index2--;
            g = g->ant;
        }
        else{
            if (notatemp < nota1){
                index1++;
                f = f->prox ;
            }
            else{
                trocaPos(lista,f,g);
                index1++;
                index2--;
                f = f->prox;
                g = g->ant;
            }
        }
    }
    f = acertaPonteiro(lista,r);
    g = acertaPonteiro(lista,index1);
    trocaPos(lista,f,g);
    return index1;

}


/*
----------------------------------------------------------------------
Funcao acertaPonteiro
  Guia os ponteiros ao longo da lista até a ordinalidade desejada.
*/
Filme *acertaPonteiro (Lista *lista,int pos){ /*ok*/

    Filme *f;
    int i = 1;
    f = lista->ini;

    while (i < pos){
        f = f->prox;
        i++;
    }
    return f;
}


/*
----------------------------------------------------------------------
Funcao trocaPos
  Recebe o registro de dois filmes f e g. Copia os dados de f em um registro
  temporário e sobrescreve g em f. Por fim copia temporário em g, efetuando assim
  uma inversão da posição dos registros na lista.
*/
void trocaPos(Lista *lista,Filme *f,Filme *g){ /*ok*/

    Filme temp;

    temp.ano = f->ano;
    temp.nota = f->nota;
    temp.votos = f->votos;
    strcpy (temp.dist,f->dist);
    strcpy (temp.nome,f->nome);

    f->ano = g->ano;
    f->nota = g->nota;
    f->votos = g->votos;
    strcpy (f->dist,g->dist);
    strcpy (f->nome,g->nome);

    g->ano = temp.ano;
    g->nota = temp.nota;
    g->votos = temp.votos;
    strcpy (g->dist,temp.dist);
    strcpy (g->nome,temp.nome);


}


/*
----------------------------------------------------------------------
Funcao mostraMenor
  Recebe três entradas (X,Y,Z) de dados e exibe uma quantidade X de filmes com nota menor ou igual a Y com pelo menos Z votos.
  Obs: Adotei a exibição dos filmes do nota menor ou igual a estabelecida
*/
void mostraMenor(Lista *lista){/*ok*/

    int qntFilmes = 0;
    int qntVotos = 0;
    float notaMax = 0;
    Filme *f = lista->ini;
    int cont = 0;
    int votoTemp = 0;
    float notaTemp = 0;

    printf ("\nQual o numero de filmes a ser mostrado : ");
    scanf ("%d",&qntFilmes);
    printf ("Qual a nota maxima : ");
    scanf ("%f",&notaMax);
    printf ("Qual o numero minimo de votos : ");
    scanf ("%d",&qntVotos);
    printf("\n");

    while(1){

        if(f == NULL || cont == qntFilmes)
            break;

        votoTemp = f->votos;
        notaTemp = f->nota;
        if (notaTemp <= notaMax && votoTemp >= qntVotos){

            printf(
            "--------------------------------------------------------------------------------\n"
            "%s (ano %d):\n"
            "\t nota %4.1f "
            "\t %6d votos "
            "\t distribuicao [%s] \n",
            f->nome, f->ano,f->nota, f->votos, f->dist);
            cont++;
        }
        f = f->prox;

    }

    printf ("\nEsses sao os %d com nota menor que %.2f e pelo menos %d votos.\n",cont,notaMax,qntVotos);



}


/*
----------------------------------------------------------------------
Funcao mostraMenor
  Recebe três entradas (X,Y,Z) de dados e exibe uma quantidade X de filmes com nota maior ou igual a Y com pelo menos Z votos.
  Obs: Adotei a exibição dos filmes do nota maior ou igual a estabelecida, diferente do executável fornecido, porém como explicitado no
  enunciado
*/
void mostraMaior(Lista *lista){ /*ok*/

    int qntFilmes = 0;
    int qntVotos = 0;
    float notaMin = 0;
    Filme *f = lista->fim;
    int cont = 0;
    int votoTemp = 0;
    float notaTemp = 0;

    printf ("\nQual o numero de filmes a ser mostrado : ");
    scanf ("%d",&qntFilmes);
    printf ("Qual a nota minima : ");
    scanf ("%f",&notaMin);
    printf ("Qual o numero minimo de votos : ");
    scanf ("%d",&qntVotos);
    printf("\n");

    while(1){

        if(f == NULL || cont == qntFilmes)
            break;

        votoTemp = f->votos;
        notaTemp = f->nota;
        if (notaTemp >= notaMin && votoTemp >= qntVotos){

            printf(
            "--------------------------------------------------------------------------------\n"
            "%s (ano %d):\n"
            "\t nota %4.1f "
            "\t %6d votos "
            "\t distribuicao [%s] \n",
            f->nome, f->ano,f->nota, f->votos, f->dist);
            cont++;
        }
        f = f->ant;

    }
    printf("--------------------------------------------------------------------------------");
    printf ("\nEsses sao os %d  com nota maior que %.2f e pelo menos %d votos.\n",cont,notaMin,qntVotos);


 }


/*
----------------------------------------------------------------------
Funcao searchWord
  Recebe uma string como entrada de dado e verifica se a expressão existe dentro de algum dos registros da lista de filmes.
*/
void searchWord(Lista *lista){ /*ok*/

    char nome[TAMNOME+1];
    Filme *f;
    int t = FALSE;
    char seek = 'n';

    f = lista->ini;

    getchar();
    printf ("\nDigite parte do nome a ser procurado : ");
    fgets(nome, sizeof(nome),stdin);
    nome[strlen(nome+1)] = '\0';

    while(f != NULL){


        t = achaPalavra((unsigned char*)nome,strlen(nome),(unsigned char*)f->nome,strlen(f->nome));

        if (t == TRUE){

            printf(
            "--------------------------------------------------------------------------------\n"
            "%s (ano %d):\n"
            "\t nota %4.1f "
            "\t %6d votos "
            "\t distribuicao [%s] \n",
            f->nome, f->ano,f->nota, f->votos, f->dist);

            printf ("\nEsse eh o filme procurado? [s/n]: ");
            scanf ("%c",&seek);

            if (seek == 's')
                return;
            else
                t = FALSE;

            getchar ();
        }
        f = f->prox;

    }

    if (seek == 'n' || t == FALSE)
        printf ("\nFilme nao encontrado\n\n");


}


/*
----------------------------------------------------------------------
Funcao removeFilme
  Recebe uma string como entrada de dado e verifica se a expressão existe dentro de algum dos registros da lista de filmes. Caso
  encontre o registro é excluido da lista caso o usuário deseje.
*/
void removeFilme(Lista *lista){ /*ok*/

    char nome[TAMNOME+1];
    Filme *f;
    int t = FALSE;
    char seek = 'n';

    f = lista->ini;

    getchar();
    printf ("\nDigite parte do nome a ser procurado : ");
    fgets(nome, sizeof(nome),stdin);
    nome[strlen(nome+1)] = '\0';

    while(f != NULL){


        t = achaPalavra((unsigned char*)nome,strlen(nome),(unsigned char*)f->nome,strlen(f->nome));

        if (t == TRUE){

            printf(
            "--------------------------------------------------------------------------------\n"
            "%s (ano %d):\n"
            "\t nota %4.1f "
            "\t %6d votos "
            "\t distribuicao [%s] \n",
            f->nome, f->ano,f->nota, f->votos, f->dist);


            printf ("\nEsse eh o filme procurado? [s/n]: ");
            scanf ("%c",&seek);

            if (seek == 's'){
                quickErase(lista,f);
                return;
            }

            else
                t = FALSE;

            getchar ();
        }
        f = f->prox;

    }

    if (seek == 'n' || t == FALSE)
        printf ("\nFilme nao encontrado\n\n");

}


/*
----------------------------------------------------------------------
Funcao quickErase
  Remove um registro de filme e organiza os ponteiros da Lista lista e da lista Filme.

  OBS: Caso haja apenas um filme na lista e este seja removido é apresentado uma mensagem
  ao usuário, o correto seria após isso o programa ser fechado pelo fato de gerar falha de
  segmentação se o usuário solicitar que seja exibido a lista vazia ou realizado uma nova leitura
  de dados, entretando como no próprio executavel não é tratado este caso julguei como desnecessário
  e irrelevante tratar este.
*/
void quickErase(Lista *lista,Filme *f){ /*ok*/

    Filme *temp1,*temp2;

    temp1 = f->ant;
    temp2 = f->prox;

    if(temp1 == NULL && temp2 == NULL){
        free(lista->ini);
        lista->ini = lista->fim = NULL;
        printf("\nLista de filmes vazia!");
        return;
    }

    if(temp1 != NULL && temp2 != NULL){
        free(temp1->prox);
        temp1->prox = temp2;
        temp2->ant = temp1;
        return;
    }
    else if(temp1 == NULL){
            free(temp2->ant);
            temp2->ant = NULL;
            lista->ini = temp2;
            return;
    }
    else if(temp2 == NULL){
            free(temp1->prox);
            temp1->prox = NULL;
            lista->fim = temp1;
            return;
        }
}


/*
//////////////////////////////////////////////////////////////////////

  7  IMPLEMENTACAO DAS FUNCOES DADAS

\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
*/

/*
  mallocSafe: testa o ponteiro devolvido por malloc
 */
void * mallocSafe (size_t n)
{
  void * pt;
  pt = malloc(n);
  if (pt == NULL) {
    printf("ERRO na alocacao de memoria.\n\n");
    exit(-1);
  }
  return pt;
}

/*
----------------------------------------------------------------------
Funcao erroLeitura
*/

void erroLeitura(char *msg, char *lin)
{
  fprintf(stderr, "Entrada invalida ignorada(%s):\n\t%s\n", msg, lin);
}

/*
----------------------------------------------------------------------
leString
  Le uma cadeia de caracteres ate encontrar um \n.
  Devolve a cadeia de caracteres apos trocar \n por \0.
*/
int leString(char str[], int max)
{
  int tam;
  scanf(" ");
  fgets(str, max, stdin);
  tam = strlen(str)-1;
  str[tam] = '\0';
  return tam;
}


/*
----------------------------------------------------------------------
Funcao leOpcao
   Le uma opcao do usuario.
*/

char leOpcao()
{
  char opcao;

  printf(
	 "======================================================================\n"
	 "  (c) Carregar um arquivo de dados\n"
	 "  (g) Gravar a lista atual em um arquivo\n"
	 "  (i) Inserir um filme\n"
	 "  (m) Mostrar todos os filmes\n"
	 "  (o) Ordenar a lista de filmes\n"
	 "  (p) Procurar a nota de um filme\n"
	 "  (r) Remover um filme\n"
	 "  (t) Mostrar N filmes com nota menor que X e pelo menos V votos\n"
	 "  (u) Mostrar N filmes com nota maior que X e pelo menos V votos\n"
	 "  (x) Sair do programa\n\n"
	 );
  printf("Digite uma opcao: ");
  scanf(" %c", &opcao);
  return opcao;
}

/*
----------------------------------------------------------------------
Funcao criaLista
   Cria uma lista de filmes vazia
*/

Lista *criaLista()
{
  Lista *lista;

  lista =  mallocSafe(sizeof(Lista));

  lista->ini = NULL;
  lista->fim    = NULL;

  return lista;
}

/*
----------------------------------------------------------------------
Funcao rIndex
  Devolve apontador para endereco do ultimo simbolo de pal que eh
  igual a letra; ou devolve NULL se nao existir simbolo igual a letra
*/

char *rIndex(char *pal, char letra)
{
  int index;

  index = strlen(pal);
  while (index > 0) {
    index--;
    if (pal[index] == letra)
      return &pal[index];
  }

  return NULL;
}

/*
----------------------------------------------------------------------
Funcao carregaLista
   Carrega uma lista de filmes a partir de um arquivo de entrada.
   O nome do arquivo deve ser lido.
*/

void carregaLista(Lista *lista)
{
  FILE *arq;
  char linha[TAMLINHA+1], *alinha, *blinha;
  char dist[11];
  int votos;
  char nome[TAMNOME+1];
  int ano;
  float nota;
  char nome_arq[101];
  int cont = 0; /* conta número de filmes lidos */

  printf("Digite o nome do arquivo: ");
  scanf(" %s", nome_arq);
  printf("Nome do arquivo de entrada: %s\n", nome_arq);
  arq = fopen(nome_arq, "r");
  if (arq == NULL) {
    printf("\nArquivo %s nao encontrado\n\n", nome_arq);
    exit(-1);
  }

  while(fgets(linha, TAMLINHA, arq) != NULL) {
    alinha = linha; /* apontador para linha */

	/* verifica se a linha contem um filme.
	   Deve começar com 6 espaços
	   e ter um digito ou ponto na setima posicao */
    if (
	strspn(linha, " ") == 6 && /* 6 caracteres brancos */
	( linha[6] == '.' ||
	 (linha[6] >= '0' && linha[6] <= '9')
	  )	                   /* inicio da distribuicao */
	) {
      alinha += 6; /* pula brancos */

      /* distribuicao, 10 caracteres */
      strncpy(dist, alinha, 10);
      dist[10] = '\0';
      alinha += 10; /* pula distribuicao */

      /* votos e nota, ocupam 16 posições */
      if (sscanf(alinha, "%d %f", &votos, &nota) != 2) {
	erroLeitura("votos ou nota invalidos", linha);
	continue;
      }
      alinha += 16; /* pula votos e nota */

      /* pula brancos e tabs */
      while (*alinha == ' ' || *alinha == '\t') alinha++;

      /* encontra ultimo '{' e joga comentarios fora */
      blinha = rIndex(alinha, '{');
      if (blinha != NULL) *blinha = '\0';

      /* procura o ano no que sobrou da linha */
      blinha = rIndex(alinha, '(');
      if (blinha == NULL) {
	erroLeitura("ano ausente", linha);
	continue;
      }

      /* nao eh ano: eh (mini), (TV) ou (V) */
      if (!isdigit(blinha[1]) && blinha[1] !=  '?') {
	*blinha = '\0';			/* joga fora */
	blinha = rIndex(alinha, '(');   /* pega o parenteses  anterior */
	if (blinha == NULL) {
	  erroLeitura("ano ausente", linha);
	  continue;
	}
      }
      blinha++;				/* pula o parenteses */

      if (sscanf(blinha, "%d", &ano) != 1) {
	/* pode ser ano ignorado */
	if (strspn(blinha, "?") == 4)
	  ano = 9999;
	else {
	  erroLeitura("ano invalido", linha);
	  continue;
	}
      }

      blinha[-2] = '\0'; /* joga fora pedaco final da linha com o ano */

      /* O que sobra eh o nome */
      strncpy(nome, alinha, TAMNOME);
      nome[TAMNOME] = '\0';

      insereFilme(lista, criaFilme(dist, votos, nota, nome, ano));
      cont++;
      if (cont % 1000 == 0) {
	printf(".");     /* indicador de progresso */
	fflush(stdout);  /* imprime o '.' sem esperar que a linha toda fique pronta */
      }
    }
  }

  printf("\n");
  fclose(arq);
}

/*
----------------------------------------------------------------------
gravaLista
  Grava a lista de filmes no arquivo nome, no formato:
     - 6     espacos
     - %s    dist
     - %7d   votos
     - %7.1  nota
     - %s    nome
     - (%d)  ano

  Exemplo
       0.0.003003      29   7.0  Always a Bridesmaid (2000)
*/

void gravaLista(Lista *lista)
{
  FILE *arq;
  char nome_arq[101];
  Filme *f;

  printf("Digite o nome do arquivo: ");
  scanf(" %s", nome_arq);
  printf("Nome do arquivo de saida: %s\n", nome_arq);
  arq = fopen(nome_arq, "w");
  if (arq == NULL) {
    printf("\nNao foi possivel criar o arquivo %s.\n\n", nome_arq);
    exit(-1);
  }

  for (f=lista->ini; f!=NULL; f=f->prox)
    fprintf(arq, "      %s %7d %7.1f\t%s\t(%d)\n",
	    f->dist, f->votos, f->nota, f->nome, f->ano);

  fclose(arq);
}

/*
----------------------------------------------------------------------
Funcao criaFilme
   Cria uma celula para armazenar um filme
*/

Filme *criaFilme(char *d, int v, float n, char *nm, int a)
{
  Filme *f;

  f = mallocSafe(sizeof(Filme));
    /*copia os dez primeiros caracteres da string para o campo distribuição dos votos*/
  strncpy(f->dist, d, 10);
  f->dist[10] = '\0';

  strncpy(f->nome, nm, TAMNOME);
  f->nome[TAMNOME] = '\0';

  f->votos = v;
  f->nota  = n;
  f->ano   = a;

  f->prox = f->ant = NULL;	/* paranoia */
  return f;
}

/*
----------------------------------------------------------------------
Funcao insereFilme
  Insere um filme na lista, mas nao verifica se ha filmes duplicados
*/
void insereFilme(Lista *lista, Filme *entrada)
{
  Filme *f;

  if (lista != NULL && !achaFilme(lista, entrada)) {
    f = lista->fim;
    if (f != NULL) {
      f->prox = entrada;
      entrada->ant = f;
      lista->fim = entrada;
    }
    else {
      lista->ini = lista->fim = entrada;
      entrada->ant = entrada->prox = NULL;
    }
  }
}

/*
----------------------------------------------------------------------
Funcao mostraUmFilme
  Imprime as informacoes sobre um filme
*/
void mostraUmFilme(Filme *f)
{
  if (f != NULL){
    printf(
	   "--------------------------------------------------------------------------------\n"
	   "%s (ano %d):\n"
	   "\t nota %4.1f "
	   "\t %6d votos "
	   "\t distribuicao [%s] \n",
	   f->nome, f->ano,f->nota, f->votos, f->dist);
  }
  else
    printf("--------------------------------------------------------------------------------\n");
}

/*
----------------------------------------------------------------------
Funcao mostraLista
   Imprime uma lista de filmes.
*/
void mostraLista(Lista *lista) /*apagar a parte adicionada depois*/
{
  Filme *f;
  int cont = 0;

  if (lista == NULL)
    {
      printf("Lista de filmes vazia.\n");
      return;
    }

  for (f = lista->ini; f != lista->fim->prox; f = f->prox) {
    mostraUmFilme(f);
    cont++;
  }
  mostraUmFilme(NULL);
  printf("Total de filmes: %d\n", cont);

}

