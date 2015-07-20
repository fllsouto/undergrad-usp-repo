/********************************************************/
/* Fellipe Souto Sampaio */
/* Exercicio-Programa EP1 */
/* Curso... Bacharelado Matem�tica - Turma... 2012 - Profa. Yoshiko Wakabayashi */
/* */
/* Compilador:... Dev-C++ 4.9.9.2 */
/********************************************************/

#include <stdio.h>
#include <stdlib.h>

int main () /*Fun��o principal*/

{
    int
    num, /*Vari�vel para realiza��o das opera��es de compara��o e soma*/
    soma,  /*Vari�vel para guardar o valor somado dos algarismos*/
    resto,  /*Vari�vel para guardar o resto da divis�o e auxiliar na decomposi��o do n�mero*/
    conta1, /*Contador suporte para realiza��o de 1 ciclo com intuito de configurar certas vari�veis*/
    valmaior, /*Vari�vel que guarda o valor do maior algarismo que constitui N*/
    valmenor,  /*Vari�vel que guarda o valor do menor algarismo que constitui N*/
    par, /*Vari�vel que guarda a quantidade de n�meros pares em N*/
    impar, /*Vari�vel que guarda a quantidade de n�meros pares em N*/
    tiponum, /*Vari�vel de suporte para identificar se o n�mero � impar ou par*/
    unid, /*Vari�vel para identifica��o do digito que compoem a casa da unidade*/
    contaunid, /*contador de quantas repeti��es do algarismo da unidade ocorre em N*/
    gnum, /*Vari�vel para guardar o valor de N*/
    ncal, /*Vari�vel suporte para continuar rodando o programa*/
    ncal2; /*Vari�vel suporte para continuar rodando o programa*/
    ncal2 = 1;
    
    
    while (ncal2 != 0)
{
    printf ("\n\tDigite um Numero Inteiro Positivo e Diferente de Zero => ");
    scanf ("%d", &num);
    
    
        /*Rotina 1 para excluir casos em que N � igual a zero ou n�meros negativos*/
    while (num ==0)
       {
            printf ("\n\tZero nao e' um numero valido");
            printf ("\n\tDigite um Numero Inteiro Positivo e Diferente de Zero =>    ");
            scanf ("%d", &num);
            while (num < 0)
            {
            printf ("\n\tNumeros negativos nao sao uma opcao valida");
            printf ("\n\tDigite um Numero Inteiro Positivo e Diferente de Zero =>    ");
            scanf ("%d", &num);
            }
       }
       
       
     /*Rotina 2 para excluir casos em que N � igual a n�meros negativos ou a zero*/
    while (num < 0)
       {
            printf ("\n\tNumeros negativos nao sao uma opcao valida");
            printf ("\n\tDigite um Numero Inteiro Positivo e Diferente de Zero =>    ");
            scanf ("%d", &num);
            while (num ==0)
            {
            printf ("\n\tZero nao e' um numero valido");
            printf ("\n\tDigite um Numero Inteiro Positivo e Diferente de Zero =>    ");
            scanf ("%d", &num);
            }
       }
    
    /*Defini��o inicial de valores para determinadas vari�veis*/
    
    resto = 0;
    conta1 = 1;
    soma = 0;
    contaunid = 0;
    gnum = num;
    unid = 0;
    
    /*Rotina Principal*/
    while (num !=0)
    {
          resto = num%10; /*Obtem o algarismo da casa da unidade que compoem o numero*/
          soma = soma+resto; /*Encontra a soma dos algarismos que compoem o numero*/
          tiponum = resto%2; /*Identifica o tipo dos algarismos do n�mero, impar ou par*/
          /*Segunda rotina de defini��o de valores para outras vari�veis*/
          while (conta1 != 0)
          {
                unid = resto;
                valmenor = 9;
                valmaior = 0;
                par = 0;
                impar = 0;
                conta1= conta1 - 1;
                }
          /*Rotina para definir o menor algarismo que compoem N*/
         if (resto <= valmenor) /* encontra o valor menor */
                    {
                   valmenor = resto;
                    }
          /*Rotina para definir o maior algarismo que compoem N*/
         if (resto >= valmaior) /* encontra o valor maior */
                   {
                   valmaior = resto;
                   }
         /*Rotina para definir quantas vezes o algarismo da unidade se repete em N */
         if ( resto == unid)
              { 
              contaunid++;
              }
        
        /*Rotina para definir se os algarismos que compoem N s�o impares ou pares*/
         if (tiponum ==0)
            {
            par++;
            }
         else
             {
             impar++;
             }
               
        num = (num-resto)/10; /*Exclui o algarismo da casa da unidade e desloca a virgula uma casa � esquerda*/
    }
    
    
    /*Rotina que apresenta os dados calculados*/
    printf ("\n\t\tO Total de Digitos Pares em %d  e'  %d\n", gnum, par);
    printf ("\n\t\tO Total de Digitos Impares em %d  e'  %d\n", gnum, impar);
    printf ("\n\t\tA Soma de Todos Algarismos de %d e' =  %d\n",gnum , soma);
    printf ("\n\t\tO Maior Algarismo Que Constitui %d e' %d \n",gnum , valmaior);
    printf ("\n\t\tO Menor Algarismo Que Constitui %d e' %d \n",gnum , valmenor);    
    printf ("\n\t\tExistem %d Digitos Iguais ao Algarismo %d \n\t\tQue Compoem a Casa da Unidade do Numero %d\n\n",contaunid, unid, gnum);
    /*Rotina para an�lise de um novo n�mero*/
    printf ("\n\n\n\t\tDeseja analisar um novo numero? \n\t\tQualquer numero.........Sim\n\t\tZero........Nao   ");
    scanf ("%d", &ncal);
    if (ncal ==0)
    {
       return 0; /*Comando para finalizar o programa*/
    }
       system ("cls"); /*Comando para limpar a tela*/
}
}
    
    
