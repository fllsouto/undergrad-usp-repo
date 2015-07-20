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

  Nome:     Fellipe Souto Sampaio
  NUSP:     7990422
  Prof:     Roberto Marcondes Cesar Junior

  EP2.c
  Mondrians

  Referências: Com exceção das rotinas fornecidas no esqueleto e em sala
  de aula, caso você tenha utilizado alguma refência, liste-as abaixo
  para que o seu programa não seja considerada plágio.
  Exemplo:
  - A função mallocSafe foi baseada na função mallocc
    retirada de: http://www.ime.usp.br/~pf/algoritmos/aulas/aloca.html

 \__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__
*/

/*
  NAO EDITE OU MODIFIQUE NADA QUE ESTA ESCRITO NESTE ESQUELETO.
  COPIE O ESQUELETO PARA UM OUTRO ARQUIVO, E EDITE AS PARTES 5 E 6
  CONTENDO A SUA SOLUÇÃO.

  A estrutura deste esqueleto esta em seguida.
  Não altere esta estrutura.

  1  DECLARACAO DE STRUCTS e TIPOS
  2  MACROS E CONSTANTES
  3  PROTOTIPOS DAS FUNCOES DADAS
  4  PROTOTIPOS DE FUNCOES QUE VOCE DEVE FAZER
  5  M A I N
  6  IMPLEMENTACAO DAS FUNCOES QUE VOCE DEVE FAZER
  7  IMPLEMENTACAO DAS FUNCOES DADAS

  As partes deste EP que você deverá escrever são:

  5  M A I N
  6  IMPLEMENTACAO DAS FUNCOES QUE VOCE DEVE FAZER
*/

#include <stdlib.h>
#include <stdio.h>


/*
//////////////////////////////////////////////////////////////////////
  1  DECLARACAO DE STRUCTS e TIPOS

\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
*/

typedef unsigned char BYTE;

struct celPixel {
  int x, y;
  struct celPixel *prox;
};
typedef struct celPixel CelPixel;


struct celRegiao {
  int tamanho;
  CelPixel cabpix;
};
typedef struct celRegiao CelRegiao;


typedef struct {
  int nL;
  int nC;
  float **pixel;
} Imagem;

struct lineStruct {
  char tipo;
  int pos, ini, fim;
  struct lineStruct *prox;
};
typedef struct lineStruct Linha;

/*
//////////////////////////////////////////////////////////////////////
  2  MACROS E CONSTANTES

\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
*/

#define TIPO_HORIZONTAL 'H'
#define TIPO_VERTICAL   'V'

#define EXIT_FAILURE_MALLOC -1

#define MAX_REGIOES 1000
#define MAX_LINHA 256

#define COR_FUNDO 1.0
#define COR_BORDA 0.0

/*
//////////////////////////////////////////////////////////////////////
  3  PROTOTIPOS DAS FUNCOES DADAS

\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
*/
void *mallocSafe (size_t nbytes);

void leMondrian(char *nomeArquivo, int *altura, int *largura, Linha *cab);

void salvaImagemRGB (char *nomeArquivo, Imagem *R, Imagem *G, Imagem *B);

void salvaImagem (char *nomeArquivo, Imagem *img);


/*
//////////////////////////////////////////////////////////////////////
  4  PROTOTIPOS DE FUNCOES QUE VOCE DEVE FAZER

\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
*/

/* Protótipos das funções que você precisa implementar */

float getPixel(Imagem *img, int x, int y);

void  setPixel(Imagem *img, int x, int y, float cor);

void  pintaImagem(Imagem *img, float cor);

void  copiaImagem (Imagem *destino, Imagem *origem);

Imagem *criaImagem(int nLins, int nCols);

void desenhaLinha(Imagem *img, Linha * lin, float cor);

void desenhaBorda(Imagem *img, float cor);

int  juntaPixels(Imagem *img, int x, int y,
		 float corNova, CelPixel *cabeca);

int  segmentaRegioes(Imagem *img, CelRegiao cabecas[MAX_REGIOES]);

void pintaRegiao(CelPixel *cab, Imagem *R, Imagem *G, Imagem *B,
		 float cor[3]);



/*
\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
  5  M A I N

//////////////////////////////////////////////////////////////////////
*/

int main(int argc, char** argv)
{

/*
\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
  5.1  Declarações de variáveis que serão utilizadas

//////////////////////////////////////////////////////////////////////
*/
    int largura,altura,i,j,numreg;

    Imagem *imgcriada,*canalRED,*canalGREEN,*canalBLUE;

    Linha *cab;

    CelRegiao *vetorreg;

    float CORES[12][3]=
            {
              {1.0, 0.0, 0.0}, /*  0 red     */
              {0.0, 1.0, 0.0}, /*  1 green   */
              {0.0, 0.0, 1.0}, /*  2 blue    */
              {1.0, 1.0, 0.0}, /*  3 yellow  */
              {1.0, 0.0, 1.0}, /*  4 magenta */
              {0.0, 0.0, 0.0}, /*  5 black   */
              {0.2, 0.7, 0.4}, /*  6 green 2 */
              {0.7, 0.4, 0.2}, /*  7 marrom  */
              {0.0, 1.0, 1.0}, /*  8 cyan    */
              {0.5, 0.5, 0.5}, /*  9 cinza   */
              {1.0, 1.0, 1.0}, /* 10 branco  */
              {0.0, 0.0, 0.0}  /* 11 preto   */
            };

/*
\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
  5.2  Criação de uma lista ligada com cabeça (1) e leitura do arquivo
  de entrada (2)

//////////////////////////////////////////////////////////////////////
*/

    cab = mallocSafe(sizeof(Linha)); /*(1)*/
    cab->prox=  NULL; /*(1)*/

    leMondrian(argv[1],&altura,&largura,cab); /*(2)*/


/*
\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
  5.3  Criação da imagem partindo dos parâmetros de entrada (3),
  pinta a imagem com a cor de fundo(4), desenha a borda (5), as
  linhas horizontais e verticais (6)

//////////////////////////////////////////////////////////////////////
*/
    imgcriada = criaImagem(altura,largura);/*(3)*/

    pintaImagem(imgcriada,COR_FUNDO);/*(4)*/

    desenhaBorda(imgcriada,COR_BORDA);/*(5)*/

    desenhaLinha(imgcriada,cab->prox,COR_BORDA);/*(6)*/

/*
\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
  5.4  Cria um vetor par agrupar listas com cabeça (7), segmenta as
  regiões, contando o seu total e o número de pixels que as compoem (8)

//////////////////////////////////////////////////////////////////////
*/
    vetorreg = mallocSafe(MAX_REGIOES*sizeof(CelRegiao)); /*(7)*/

    numreg = segmentaRegioes(imgcriada, vetorreg); /*(8)*/

/*
\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
  5.5  Criação dos canais de cor (9) e duplicação da imagem original
  (10)

//////////////////////////////////////////////////////////////////////
*/
    canalBLUE = criaImagem(imgcriada->nL,imgcriada->nC); /*(9)*/
    copiaImagem(canalBLUE,imgcriada); /*(10)*/


    canalGREEN = criaImagem(imgcriada->nL,imgcriada->nC); /*(9)*/
    copiaImagem(canalGREEN,imgcriada); /*(10)*/


    canalRED = criaImagem(imgcriada->nL,imgcriada->nC); /*(9)*/
    copiaImagem(canalRED,imgcriada); /*(10)*/

/*
\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
  5.5  Pintura da imagem utilizando os filtros RGB (11) e salvamento
  da imagem colorida (12)

//////////////////////////////////////////////////////////////////////
*/
    /*salvaImagem(argv[2],imgcriada);*/
    /*OBS : Como o intuito do programa é ter uma imagem colorida como saída
    não faz sentido deixar a função acima ativada, sua saida seria apagada
    pela saida RGB, que utiliza o mesmo nome como argumento na função*/

    j = 0;

    for (i = 1; i <= numreg; i++){
        pintaRegiao(&vetorreg[i].cabpix, canalRED, canalGREEN, canalBLUE,CORES[j]);

        j = j+2;
        if (j == 10)
            j = 1;
        if (j == 11)
            j = 0;

    }/*(11)*/

    salvaImagemRGB (argv[2], canalRED,canalGREEN,canalBLUE); /*(12)*/

  return 0;
}

/*
//////////////////////////////////////////////////////////////////////
  6  IMPLEMENTACAO DAS FUNCOES QUE VOCE DEVE FAZER

\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
*/


/*
//////////////////////////////////////////////////////////////////////
    6.1  MANIPULAÇÃO DE IMAGENS

\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
*/

/*
//////////////////////////////////////////////////////////////////////
    getPixel -   A função getPixel devolve o valor/cor do pixel da
    posição (x,y) da imagem *img.
\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
*/

float getPixel(Imagem *img, int x, int y){

    return img->pixel[x][y];
}

/*
//////////////////////////////////////////////////////////////////////
    setPixel -   A função setPixel coloca o valor cor no pixel da
    posição (x,y) da imagem *img.
\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
*/

void  setPixel(Imagem *img, int x, int y, float cor){

    img->pixel[x][y] = cor;
}

/*
//////////////////////////////////////////////////////////////////////
    pintaImagem -   A função pintaImagem coloca o valor cor em todos
    os pixels da imagem *img.
\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
*/

void  pintaImagem(Imagem *img, float cor){

    int i,j;

    for (i = 0; i < img->nL ; i++ )
        for ( j = 0 ; j < img->nC ; j++ )
            setPixel(img,i,j,cor);

}

/*
//////////////////////////////////////////////////////////////////////
    copiaImagem -   A função copiaImagem copia a imagem *origem na
    imagem *destino.
\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
*/


void  copiaImagem (Imagem *destino, Imagem *origem){

    int i,j;

    for(i = 0 ; i < origem->nL ; i++ )
        for (j = 0 ; j < origem->nC ; j++ )
            destino->pixel[i][j] = origem->pixel[i][j];
}

/*
//////////////////////////////////////////////////////////////////////
    *criaImagem -   A função criaImagem recebe o número de linhas nLins
    e o número de colunas nCols, cria um registro do tipo Imagem,
    alocando uma matriz de dimensão nLins nCols, e devolve o endereço
    do registro que foi criado.
\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
*/

Imagem *criaImagem(int nLins, int nCols){

    Imagem *p;
    int i;

    p = mallocSafe(sizeof(Imagem));
    p->nL = nLins;
    p->nC = nCols;
    p->pixel = mallocSafe(nLins*sizeof(float *));

    for (i=0;i<nLins;i++)
        p->pixel[i] = mallocSafe(nCols*sizeof(float));

    return (p);
}

/*
//////////////////////////////////////////////////////////////////////
    6.2 DESENHO DE LINHAS

\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
*/

/*
//////////////////////////////////////////////////////////////////////
    desenhaLinha -   A função desenhaLinha desenha uma linha dada
    por *lin, com a cor cor na imagem *img.
\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
*/

void desenhaLinha(Imagem *img, Linha * lin, float cor){

    int i;
    Linha *elemento;

    for (elemento = lin; elemento != NULL ; elemento = elemento->prox){

        if (elemento->tipo == 'H'||elemento->tipo == 'h')
            for (i=elemento->ini;i<elemento->fim;i++)
                setPixel(img,elemento->pos,i,cor);


         if (elemento->tipo == 'V'||elemento->tipo == 'v')
             for (i=elemento->ini;i<elemento->fim;i++)
                setPixel(img,i,elemento->pos,cor);

    }

}

/*
//////////////////////////////////////////////////////////////////////
    desenhaBorda -   A função desenhaBorda desenha uma borda com a cor
    "cor" ao redor da imagem *img. A borda é determinada através do
    campos nL e nC do resgitro *img. A borda definida pelas linhas
    0 e nL-1 e colunas 0 e nC-1.
\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
*/

void desenhaBorda(Imagem *img, float cor){

    int i;

    for (i = 0; i < img->nC ; i++)
        setPixel(img,0,i,cor);

    for (i = 0; i < img->nC ; i++)
        setPixel(img,img->nL-1,i,cor);

    for (i = img->nL ; 0 < i ; i--)
        setPixel(img,i-1,0,cor);

    for (i = img->nL ; 0 < i ; i--)
        setPixel(img,i-1,img->nC-1,cor);

}

/*
//////////////////////////////////////////////////////////////////////
    6.3 SEGMENTAÇÃO DAS REGIÕES

\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
*/

/*
//////////////////////////////////////////////////////////////////////
    juntaPixels -  A função juntaPixels recebe a posição (x,y) de um
    ponto dentro de uma região da imagem *img e agrupa os pixels dessa
    região, colocando-os em uma lista ligada com cabeça *cabeca
\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
*/

int  juntaPixels(Imagem *img, int x, int y,float corNova, CelPixel *cabeca){

    int contapixel;
    CelPixel *nova;
    contapixel = 0;


    if (getPixel(img,x,y) != COR_FUNDO)
        return 0;
    else{
        setPixel(img,x,y,corNova);
        contapixel++;

        nova = mallocSafe(sizeof(CelPixel));
        nova->prox = cabeca->prox;
        cabeca->prox = nova;
        cabeca->x = x;
        cabeca->y = y;
        contapixel+= juntaPixels(img,x-1,y,corNova,nova); /*cima*/
        contapixel+= juntaPixels(img,x+1,y,corNova,nova); /*baixo*/
        contapixel+= juntaPixels(img,x,y-1,corNova,nova); /*esquerda*/
        contapixel+= juntaPixels(img,x,y+1,corNova,nova); /*direita*/
    }



    return contapixel;

}

/*
//////////////////////////////////////////////////////////////////////
    segmentaRegioes -  A função segmentaRegioes deve varrer a imagem
    *img e devolver o número de regiões encontradas.
\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
*/

int  segmentaRegioes(Imagem *img, CelRegiao cabecas[MAX_REGIOES]){

    int contareg,i,j;
    CelPixel *p;
    float corr;
    contareg = 0;
    corr = 0.9;

    fprintf (stdout,"\nGrupos de pixeis conexos: \n");

    for (i = 0; i <img->nL ; i++)
        for (j = 0; j < img->nC ; j++)

            if (getPixel(img,i,j) == COR_FUNDO){
                contareg++;
                corr = corr-0.05;

                p = mallocSafe(sizeof(CelPixel));
                p->prox = NULL;
                p->x = i;
                p->y = j;

                cabecas[contareg].tamanho = juntaPixels(img,i,j,corr,p);
                cabecas[contareg].cabpix = *p;
                fprintf (stdout,"Grupo %d tem %d pixels\n",contareg-1,cabecas[contareg].tamanho);
            }

    fprintf (stdout,"\n");

    return contareg;
}

/*
//////////////////////////////////////////////////////////////////////
    6.4 PINTURA COM UMA COR RGB

\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
*/

/*
//////////////////////////////////////////////////////////////////////
    pintaRegiao -   A função pintaRegiao recebe

    1 - a célula cabeça *cab de uma lista encadeada de pixels que formam
    uma região;
    2 - os três canais *R, *G e *B que representam uma imagem colorida;
    3 - uma cor RGB dada por um vetor cor de tal forma que (cor[0],cor[1]
    ,cor[2]) é a combinação RGB da cor,

    E pinta cada canal com sua intensidade correspondente
\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
*/

void pintaRegiao(CelPixel *cab, Imagem *R, Imagem *G, Imagem *B,float cor[3]){

    CelPixel *elemento;

    for (elemento = cab; elemento!= NULL ; elemento = elemento->prox){

        setPixel(R,elemento->x,elemento->y,cor[0]);
        setPixel(G,elemento->x,elemento->y,cor[1]);
        setPixel(B,elemento->x,elemento->y,cor[2]);

   }

}

/*
\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
  7  IMPLEMENTACAO DAS FUNCOES DADAS

//////////////////////////////////////////////////////////////////////
*/

/* *****************************************************************
   mallocSafe: testa o malloc para ver se o ponteiro é válido
 */
void *mallocSafe (size_t nbytes)
{
   void *ptr;
   ptr = malloc (nbytes);
   if (ptr == NULL) {
     fprintf (stderr, "Socorro! malloc devolveu NULL!\n");
     exit (EXIT_FAILURE_MALLOC);
   }
   return ptr;
}


/* *****************************************************************
  salvaImagem RGB organizada em 3 imagens cinza no formato ppm
  Assumindo origem no canto inferior esquerdo.
 */
void salvaImagemRGB(char *nomeArquivo, Imagem *R, Imagem *G, Imagem *B)
{
  int i, j;
  char nome[256];
  FILE *fp;
  sprintf(nome, "%s.ppm", nomeArquivo);
  fp = fopen(nome, "wb");

  fprintf(fp, "P6\n%d %d\n255\n", R->nC, R->nL);

  for (i = R->nL - 1; i>=0; i--)
    for (j = 0; j < R->nC; j++)
      fprintf(fp, "%c%c%c",
	      (BYTE)(255*R->pixel[i][j]),
	      (BYTE)(255*G->pixel[i][j]),
	      (BYTE)(255*B->pixel[i][j]));

  fprintf(stdout, "A imagem colorida foi salva no arquivo: %s\n", nome);
  fclose(fp);
}

/* *****************************************************************
  salvaImagem cinza no formato pgm
 */
void salvaImagem(char *nomeArquivo, Imagem *img)
{
  int i, j;
  char nome[256];
  FILE *fp;
  sprintf(nome, "%s.pgm", nomeArquivo);
  fp = fopen(nome, "wb");

  fprintf(fp, "P5\n%d %d\n255\n", img->nC, img->nL);

  for (i = img->nL - 1; i>=0; i--)
    for (j = 0; j < img->nC; j++)
      fprintf(fp, "%c", (BYTE)(255*img->pixel[i][j]));

  fprintf(stdout, "A imagem foi salva no arquivo: %s\n", nome);
  fclose(fp);
}

/* *****************************************************************
  carrega Linhas
 */

void leMondrian(char *nomeArquivo, int *altura, int *largura, Linha *cab)
{
  char aux[MAX_LINHA];
  int npars;
  FILE *entrada;
  int p, i, f;
  Linha *nova;
  int cont = 0;

  entrada = fopen(nomeArquivo, "r");
  if (entrada == NULL)
    {
      fprintf(stderr, "ERRO!! Nao consegui abrir o arquivo %s\n", nomeArquivo);
      exit(-1);
    }
  fprintf(stdout, "Arquivo de entrada com a definicao do desenho: %s\n",
	  nomeArquivo);
  while (fscanf(entrada, "%s", aux) != EOF)
    {

      switch (aux[0]) {
      case '#':
	fgets(aux, MAX_LINHA, entrada);
	break;

      case 'r':
      case 'R':
	npars = fscanf(entrada, "%d %d", altura, largura);
	if (npars != 2) {
	  fprintf(stderr, "ERRO na leitura da dimensao da"
		  " imagem no arquivo de entrada %s\n", nomeArquivo);
	  exit (-1);
	}
	else {
	  fprintf(stdout, "Resolucao da Imagem: %d linhas x %d colunas \n",
		  *altura, *largura);
	}
	break;

      case 'H':
      case 'h':
	npars = fscanf(entrada, "%d %d %d", &p, &i, &f);
	if (npars != 3) {
	  fprintf(stderr, "ERRO na leitura de uma linha horizontal"
		  " no arquivo de entrada %s\n", nomeArquivo);
	  exit (-1);
	}
	else {
	  cont += 1;
	  nova = mallocSafe(sizeof(Linha));
	  nova->prox = cab->prox;
	  nova->tipo = TIPO_HORIZONTAL;
	  nova->pos = p;
	  nova->ini = i;
	  nova->fim = f;

	  cab->prox = nova;
	  fprintf(stdout, "Linha %3d: Tipo H com pos = %4d, "
		  "inicio = %4d e fim %4d\n",
		  cont, p, i, f);
	}
	break;

      case 'V':
      case 'v':
	npars = fscanf(entrada, "%d %d %d", &p, &i, &f);
	if (npars != 3) {
	  fprintf(stderr, "ERRO na leitura de uma linha vertical no"
		  " arquivo de entrada %s\n", nomeArquivo);
	  exit (-1);
	}
	else {
	  cont += 1;
	  nova = mallocSafe(sizeof(Linha));
	  nova->prox = cab->prox;
	  nova->tipo = TIPO_VERTICAL;
	  nova->pos = p;
	  nova->ini = i;
	  nova->fim = f;

	  cab->prox = nova;
	  fprintf(stdout, "Linha %3d: Tipo V com pos = %4d, "
		  "inicio = %4d e fim %4d\n", cont, p, i, f);
	}
	break;

      default:
	fgets(aux, MAX_LINHA, entrada);
	break;
      }
    }
  fclose(entrada);
}


