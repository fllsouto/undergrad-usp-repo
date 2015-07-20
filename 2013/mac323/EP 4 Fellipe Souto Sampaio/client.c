/*

  Nome:     Fellipe Souto Sampaio
  NUSP:     7990422

  Prof:     Yoshiharu Kohayakawa
  Disciplina: MAC0323 - Estrutura de dados
*/
/****************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "readBook.h"
#include "interface.h"



int main (int argc,char *argv[]){
	
	char bookName[128]; /*Tamanho máximo para o título de um livro*/
	char opt[10];
	char word[256];/*Tamanho máximo permitido para uma palavra*/
	int ret = 0;
	ret = sscanf(argv[1],"-f%s",bookName);
	
	if (ret != 1){
		printf ("Entrada invalida, programa abortado!\n");
		exit(-1);
	}
	
	printf ("Bem vindo, livro inserido : %s\n",bookName);
	printf ("Inicilizando tabela hashing\n");
	STstart();
	printf ("Carregando Livro.....\n");
	STstartReadBook(bookName);

	printf ("Livro Carregado.....\n");
	printf ("Insira uma opcao e palavra : ");
	fscanf (stdin,"-%s %s",opt,word);
	clear_newlines();
	while (strcmp(opt,"F") != 0){
		if (strcmp(opt,"e") == 0)
			STseekWord(word,'e');
		if (strcmp(opt,"ev") == 0)
			STseekWord(word,'v');
		if (strcmp(opt,"eV") == 0)
			STseekWord(word,'V');
		if (strcmp(opt,"a") == 0)
			STseekLemma(word, 'a');
		if (strcmp(opt,"av") == 0)
			STseekLemma(word,'v');
		if (strcmp(opt,"aV") == 0)
			STseekLemma(word,'V');
		
		printf ("Insira uma opcao e palavra : ");
		fscanf (stdin,"-%s %s",opt,word);
		clear_newlines();
	}
	
	
	printf ("Fim de Programa!\n");
	
	return 0;

}
