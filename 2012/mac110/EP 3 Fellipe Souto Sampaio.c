/********************************************************/
/* Fellipe Souto Sampaio                                */
/* N�mero USP : 7990422                                 */
/* Exercicio-Programa - Lojas PontoChic EP3             */
/* Curso: Bacharelado Matem�tica - Turma: 2012 -        */
/* Profa. Yoshiko Wakabayashi                           */
/* Compilador: Code :: Blocks 10.05                     */
/********************************************************/

#include <stdio.h>
#include <math.h>
#define ENTRADA "entrada.txt"
#define SAIDA "saida.txt"


double pot_n (double jur, int n_mes);
/*devolve a e-n�sima pot�ncia de x */

double valor_a_vista (double prest,double jur, int n_mes);
/*devolve o valor a vista */

double valor_prestacao(double valvista,double jur, int n_mes);
/*devolve o valor da presta��o */

int max_mes (double valvista, double prest, double jur);
/*devolve o valor do maximo mes */

double prest_max (double valvista,double jur, int m_mes);
/*devolve o valor da presta��o m�xima */

double x_fxj (double valvista, double prest, double jur,int n_mes);
/*Devolve o valor de Fj(x) */

double x_dxj (double valvista, double prest, double jur,int n_mes);
/*Devolve o valor de Fj'(x) */

double valor_juros(double valvista,double prest, int n_mes);
/*Devolve o valor do juros atrav�s do m�todo de newton para c�lculo da raiz */


int main ()

    {
        printf ("\t*********** Programa para calculo de funcoes financeiras ***********\n");
        FILE *entrada,*saida;
        int n_mes,m_max;
        float valvista,prest,p_max,juros;
        char codigo;

        entrada = fopen (ENTRADA, "r");
        if (entrada == NULL)
        {
            printf ("ERRO: arquivo de entrada nao encontrado\n");
            return -1;
        }

        saida = fopen (SAIDA, "w");
        if (saida == NULL)
        {
            printf ("ERRO: arquivo de saida nao pode ser gravado\n");
            return -1;
        }
        fprintf(saida,"****************************************************************\n");
        fprintf(saida,"***                                                          ***\n");
        fprintf(saida,"***    MAC0110 - Introducao a Computacao - 1o. semestre 2012 ***\n");
        fprintf(saida,"***    Terceiro Exercicio-Programa (EP3)                     ***\n");
        fprintf(saida,"***                                                          ***\n");
        fprintf(saida,"***    Aluno : Fellipe Souto Sampaio                         ***\n");
        fprintf(saida,"***    Numero USP : 7990422                                  ***\n");
        fprintf(saida,"***    Curso : Bacharelado Matem�tica                        ***\n");
        fprintf(saida,"***                                                          ***\n");
        fprintf(saida,"****************************************************************\n\n\n");

        while (!feof (entrada))
        {

            fscanf (entrada, "%c",&codigo);

            switch (codigo)
            {
                case 'v':
                fscanf(entrada, "%f %f %d ", &prest, &juros, &n_mes);
                valvista = valor_a_vista(prest,juros*0.01,n_mes);
                fprintf(saida, "****************************************************************\n\n");
                fprintf(saida, "Queremos calcular o valor a vista!\n");
                fprintf(saida, "Valor da prestacao: %.2f\n", prest);
                fprintf(saida, "Valor dos juros: %.2f%%\n", juros);
                fprintf(saida, "Numero de meses: %d\n", n_mes);
                fprintf(saida, "Valor a vista: %.2lf\n\n", valvista);
                fprintf(saida, "****************************************************************\n\n");

                break;

                case 'p':
                fscanf(entrada, "%f %f %d ", &valvista, &juros, &n_mes);
                prest = valor_prestacao (valvista,juros*0.01,n_mes);
                fprintf(saida, "****************************************************************\n\n");
                fprintf(saida, "Queremos calcular o valor das prestacoes!\n");
                fprintf(saida, "Valor a vista: %.2f\n", valvista);
                fprintf(saida, "Valor dos juros: %.2f%%\n", juros);
                fprintf(saida, "Numero de meses: %d\n", n_mes);
                fprintf(saida, "Valor da prestacao: %.2lf\n\n", prest);
                fprintf(saida, "****************************************************************\n\n");
                break;

                case 'j':
                fscanf(entrada, "%f %f %d ", &valvista, &prest, &n_mes);
                juros = valor_juros (valvista,prest,n_mes);
                fprintf(saida, "****************************************************************\n\n");
                fprintf(saida, "Queremos calcular o valor dos juros!\n");
                fprintf(saida, "Valor a vista: %.2f\n", valvista);
                fprintf(saida, "Valor da prestacao: %.2f\n", prest);
                fprintf(saida, "Numero de meses: %d\n", n_mes);
                fprintf(saida, "Valor dos juros: %.2f%%\n\n", juros*100);
                fprintf(saida, "****************************************************************\n\n");
                break;

                case 'n':
                fscanf(entrada, "%f %f %f ", &valvista, &prest, &juros);
                m_max = max_mes(valvista,prest,juros*0.01);
                p_max = prest_max(valvista,juros*0.01,m_max);
                fprintf(saida, "****************************************************************\n\n");
                fprintf(saida, "Queremos calcular o valor da prestacao e o numero de meses!\n");
                fprintf(saida, "Valor a vista: %.2f\n", valvista);
                fprintf(saida, "Valor maximo da prestacao: %.2f\n", prest);
                fprintf(saida, "Valor dos juros: %.2f%%\n", juros);

                if (p_max > prest)
                    fprintf (saida, "Nao e' possivel pagar o valor a vista\n\n");

                else
                    fprintf(saida, "Valor da prestacao: %.2lf Numero de meses: %d\n\n", p_max,m_max);

                fprintf(saida, "****************************************************************\n\n");

                break;

                default:
                /* Leia e ignore os caracteres ate' o fim da linha. */
                while (codigo != '\n' && !feof(entrada))
                fscanf(entrada, "%c", &codigo);
                break;

            }
        }
        printf ("\n\t\t  Arquivo de saida.txt criado com sucesso");
        printf ("\n\n\t\t\t****** FIM DO PROGRAMA ******\n\n");
        fclose(entrada); /* Libera os recursos do sistema que estavam sendo usados */
        fclose(saida); /* para controlar o acesso aos arquivos. */
        return 0; /* Terminou normalmente. */
}

double pot_n (double jur, int n_mes)
    {
    int i;
    double pot=1.0;

    for (i=0;i < n_mes;i++)
        pot *= (1+jur);

    return (pot);
}

double valor_a_vista (double prest,double jur, int n_mes)
    {
        double valvista;
        valvista = (prest/jur)*(1+jur-(1/pot_n(jur,n_mes-1)));
        return (valvista);
    }

double valor_prestacao(double valvista,double jur, int n_mes)
    {
        double prest;
        prest= (valvista*jur)/(1+jur -(1/pot_n(jur,n_mes-1)));
        return (prest);
    }

int max_mes (double valvista, double prest, double jur)

    {
        int x_mes = 96;
        double val;

        while(1)
        {
            val = (prest/jur)*(1+jur -(1/(pot_n(jur,x_mes-1))));
            if (val-valvista < 0.01)
                break;

            x_mes--;
        }
        return (x_mes);

    }


double prest_max (double valvista,double jur, int m_mes)
    {
        double p_max;
        p_max= (valvista*jur)/(1+jur -(1/pot_n(jur,m_mes-1)));
        return (p_max);
    }


double x_fxj (double valvista, double prest, double jur,int n_mes)
    {
        double fxj;
        fxj = valvista - (prest/jur)*(1+jur-(1/(pot_n(jur,n_mes-1))));
        return (fxj);
    }


double x_dxj (double valvista, double prest, double jur,int n_mes)
    {
        double dxj;
        dxj = (prest/(jur*jur)) * (1+jur-1/(pot_n(jur,n_mes-1))) - (prest/jur) * (1+ (n_mes-1)/(pot_n(jur , n_mes)));
        return (dxj);
    }


double valor_juros(double valvista,double prest, int n_mes)
    {
        double raiz,jur = 0.1,tol=0.0001,fx,dx;

        while (1)
        {
            fx = x_fxj(valvista,prest,jur,n_mes);
            dx = x_dxj(valvista,prest,jur,n_mes);
            raiz = jur - (fx/dx);

            if (fabs(raiz-jur)<= tol || fabs(fx)<= tol)
                break;

            jur = raiz;
        }
        return (raiz);
    }


/*....................................Descri��o..das..Vari�veis............................................................................*/

/*..........................................Fun��o..Main...................................................................................*/
/* n_mes :Guarda o valor dos meses fornecidos                                                                                              */
/* m_max :Devolve o valor m�ximo de meses c�lculados                                                                                       */
/* valvista : Guarda/Devolve o valor a vista fornecido/c�lculado                                                                           */
/* prest: Guarda/Devolve o valor da presta��o fornecido/c�lculado                                                                          */
/* p_max :Devolve o valor m�ximo da presta��o c�lculado                                                                                    */
/* juros :Guarda/Devolve o valor dos juros fornecido/c�lculado                                                                             */
/* codigo :Vari�vel para leitura da op��o escolhido no c�lculo das fun��es                                                                 */


/*..........................................Fun��o..Pot_n..................................................................................*/
/* Pot : Vari�vel que guarda o valor da en�sima pot�ncia de base (1+j)                                                                     */
/* i : Vari�vel contadora do expoente da pot�ncia                                                                                          */


/*.......................................Fun��o..Valor_a_vista.............................................................................*/
/* valvista : Guarda o valor a vista c�lculado pela fun��o                                                                                 */


/*....................................Fun��o..Valor_da_prestacao...........................................................................*/
/* prest : Guarda o valor da presta��o c�lculado pela fun��o                                                                               */


/*.......................................Fun��o..Max_mes...................................................................................*/
/* x_mes : Vari�vel contadora de meses m�ximos                                                                                             */
/* val : Vari�vel que armazena os valores a vista c�lculados dentro do la�o                                                                */


/*.......................................Fun��o..Prest_max..........................................................................       */
/* p_max : Guarda o valor da presta��o m�xima c�lculado pela fun��o                                                                        */


/*....................................Fun��o..X_fxj.........................................................................................*/
/* x_fxj : Guarda o valor de fj(x) c�lculado a partir da vari�vel jur                                                                       */


/*....................................Fun��o..X_dxj.........................................................................................*/
/* x_dxj : Guarda o valor de fj'(x) c�lculado a partir da vari�vel jur                                                                      */

/*....................................Fun��o..Valor_juros...................................................................................*/
/* raiz :Guarda os valores encontrados da ra�z Xi+1 atrav�s o m�doto de newton                                                              */
/* jur : Guarda o valor  inicial de Xi  e os valores intermedi�tios das atribui��es de Xi+1                                                 */
/* tol : Vari�vel para o controle da toler�ncia da raiz                                                                                     */
/* fx : Vari�vel que armazena o valor da fun��o x_fxj c�lculada em Xi                                                                       */
/* dx : Vari�vel que armazena o valor da fun��o x_djx c�lculada em Xi                                                                       */

