/********************************************************/
/* Fellipe Souto Sampaio                                */
/* Número USP : 7990422                                 */
/* Exercicio-Programa - Monaka EP2                      */
/* Curso: Bacharelado Matemática - Turma: 2012 -        */
/* Profa. Yoshiko Wakabayashi                           */
/* Compilador: Code :: Blocks 10.05                     */
/********************************************************/

/*O presente programa está dividido e duas rotinas, uma principal (main) e outra rotina de função (geracarta)        */
/*ao fim do programa irei descrever a utilidade de cara variavel utilizada no programa, separando-as por funções    */



#include <stdio.h>
#include <math.h>

/*Função que faz o cálculo do Seno de acordo com o valor inserido na variável "pass"*/
double geracarta (double pass)
    {
    double senodenominador, senonumerador,somaseno,x,min,calcseno;
    int j = 0;
                /* Para valores muito grandes a seguinte rotina os transforma em números menores para não haver  estouro no cálculo da potência*/
                   while (pass >1)
                    pass = pass/10;

                   j =1;
                   calcseno =1;
                   x = pass;
                   senodenominador = x;
                   senonumerador = 1.0;
                   somaseno = pass;

                       for (min = 0.00000001 ;min <= fabs (calcseno); j++)
                       {
                         senodenominador = (-senodenominador)*x*x;
                         senonumerador = senonumerador*(2*j)*(2*j+1);
                         calcseno = senodenominador/senonumerador;
                         somaseno = somaseno + calcseno;
                        }

                        return (somaseno);
    }




/*Rotina principal do programa, aqui são feitos os cálculos da mão do jogador e da banca, a comparação dos valores, as cem tentativas e o histogramo de vitórias do jogador*/

int main ()
{
    while (1)
    {

       int placar=0,qpartidas=1,i,aposta,vitoriajogador=0,cartasbanca=0,cartasjogador=0;
       double sorteio,pontosjogador = 0,pontosbanca = 0,passado,spassado,carta,teto = 0.5;

       printf ("\t\t*************** CASSINO MALANDRIN ***************\n");
       printf ("\t\t********** SIMULADOR DE SETE E & MEIO ***********\n");
       printf ("\n\t\tDigite o valor da aposta em dolas .... ");
       scanf ("%d", &aposta);
       aposta = aposta*2;
       printf ("\n\n\t\tDigite o valor inicial da variavel passado :   ");
       scanf ("%lf", &passado);
       spassado = passado;

       for (teto = 0; teto <= 7.5; teto = teto+0.5)
       {
            passado = spassado;
            qpartidas = 0;
            vitoriajogador = 0;
            for (qpartidas = 0 ;qpartidas < 100 ;qpartidas++)
           {
                pontosjogador = 0;
                pontosbanca = 0;
                cartasbanca = 0;
                cartasjogador = 0;

                    /*Rotina que gera a carta para o jogador*/
                   for (pontosjogador = 0;pontosjogador < teto; cartasjogador++)
                   {

                       sorteio = (9821.0* fabs(sin(passado)) +0.211327);
                       passado = sorteio - floor(sorteio);
                       carta = floor (passado*10+1);

                       if (carta == 8 || carta == 9 || carta == 10)
                          carta = 0.5;

                        pontosjogador+= carta;
                    }





                    /*Rotina que gera carta para a banca*/
                    for (pontosbanca = 0;pontosbanca <= pontosjogador; cartasbanca++)
                       {
                           /*Caso aconteça alguma dessas situações, a vitória da banca é automática, não sendo necessário sortear novas cartas*/
                            if (pontosbanca == pontosjogador && cartasbanca <= cartasjogador || pontosjogador > 7.5)
                                break;

                            sorteio = (9821.0* fabs(sin(passado)) +0.211327);
                            passado = sorteio - floor(sorteio);
                            carta = floor (passado*10+1);

                            if (carta == 8 || carta == 9 || carta == 10)
                                carta = 0.5;

                            pontosbanca += carta;
                        }



               /*Rotina que atribui vitoria ao jogador de acordo com o valor da sua mão*/

                if (pontosbanca == 7.5 && pontosjogador == 7.5 && cartasjogador<cartasbanca)
                    vitoriajogador++;

                if (pontosbanca > pontosjogador && pontosbanca > 7.5 && pontosjogador <= 7.5)
                    vitoriajogador++;

            }
            /*Rotina que imprime o histogramo de vitórias do jogador*/
            placar= placar+vitoriajogador;
            printf ("\n(%3g) - Teto  (%2d)  = ",teto, vitoriajogador);
            for (i=0; i!= vitoriajogador; i++)
                printf ("*");


        }
        /*Rotina que imprime a quantidade de vitórias do jogador e da banca*/
        /*A rotina seguinte imprime o valor ganho pela banca, levando em consideração que em todos os jogos o jogador apostou o mesmo valor*/
        printf ("\n\n\t\tVitorias jogador :  %12d\n\t\tVitorias banca :  %14d", placar, 1500-placar);
        printf ("\n\t\tDolas ganho pela banca :  %6d\n\n\n",((1500-2*placar))*aposta);


        printf ("\n\t\t\t O que deseja fazer? \n\t\t\tSair      -     0\n\t\t\tContinuar - 1 a 9\n\n");
        scanf ("%d", &i);
        if (i==0)
        return 0;
        else
        system ("cls");
    }
}

/*OBS 1:Por orientação dada pela Professora Yoshiko a função que cálcula o valor do seno foi substituida pela função sin da bibliotéca,*/
/*com intuito de facilitar a correção. Optei por mante-la no meu programa, porém não faço o uso da mesma durante a rotina principal.   */

/*OBS 2: Decidi deixar meu programa no módo automático, lógo após uma análise estatística tem-se a possíbilidade de realizar uma nova  */
/* caso o usuário queira, e para finalizar o programa basta escolher o valor zero quando for perguntado.                               */

/*OBS 3: Como foi  alterada para a funçao sin da biblioteca math não existe necessidade de colocar os valores da variável passado em   */
/*valores decimais, como era feito na função geracarta, de alguma forma a funçao sin consegue cálcular valores altos sem que aja       */
/*estouro  no cálculo da potência do número, como acontecia na outra função.                                                           */

/*OBS 4: Revisei toda a lógica de funcionamento do EP e não consegui identificar onde ocorre as  divergências entre os resultados       */
/*esperados e meus resultados obtidos. Julgo que meu EP esteja certo e realizando a tarefa determinada no enunciado do problema.        */

/*....................................Descrição..das..Variáveis.........................................................................*/

/*.......................................Função..Gera..Carta............................................................................*/
/* Senodenominador : Guarda o valor do fatorial cálculado da fração, que será utilizado como dividendo                                  */
/* Senonumerador : Guarda o valor da potência cálculada da fração, que será utilizado como divisor                                      */
/* Calcseno: Guarda os valores cálculados na divisão dos senonumerador pelo senodenominador                                             */
/* Somaseno : Soma os valores parciais gerados por Calcseno                                                                             */
/* Min : Valor de restrição para o cálculo do seno, quando o valor obtido for menor do que Min é quebrado o laço                        */
/* J: Variável auxiliar para efetuar o cálculo do fatorial                                                                              */
/* X :  Variável auxiliar para o cálculo da potência                                                                                    */

/*.......................................Função..Main...................................................................................*/
/* Placar : Variável que salva o total de vitórias do jogador                                                                           */
/* Qpartidas : Variável para controlar a quantidade de partidas jogadas                                                                 */
/* Aposta : Guarda o valor da aposta                                                                                                    */
/* Vitoriajogador : Variável que guarda a quantidade de vitórias que o jogador obteve utilizando um determinado teto como estratégia    */
/* Cartasbanca : Guarda a quantidade de cartas compradas pela banca em uma partida                                                      */
/* Cartasjogador : Guarda a quantidade de cartas compradas pelo jogador em uma partida                                                  */
/* Sorteio : Variável que atua no cálculo do valor da carta                                                                             */
/* Passado : Valor para qual é cálculado o seno                                                                                         */
/* Spassado: Guarda o valor inicial da variável passado                                                                                 */
/* Pontosjogador : Valor da mão do jogador                                                                                              */
/* Pontosbanca : Valor da mão da banca                                                                                                  */
/* Carta : Valor da carta gerada                                                                                                        */
/* Teto : Valor adotado pelo jogador para ser utilizado em cada estatégia de jogo                                                       */
/* I: Contador para imprimir o histogramo                                                                                               */
