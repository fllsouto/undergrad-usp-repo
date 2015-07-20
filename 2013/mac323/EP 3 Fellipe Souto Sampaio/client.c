/*
 \__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__


  Nome:     Fellipe Souto Sampaio
  NUSP:     7990422

  Prof:     Yoshiharu Kohayakawa
  Disciplina: MAC0323 - Estrutura de dados


   LOCALIZAĆÃO DE PALAVRAS I
  -client.c
  -interface.c
  -interface.h
  -itemLemma.c
  -itemLemma.h
  -itemWord.c
  -itemword.h
  -lemmaTree.c
  -lemmaTree.h
  -wordTree.c
  -wordTree.h
  -readBook.c
  -readBook.h
  -RelatórioEP3.pdf
  -makefile

  Junho de 2013.
 \__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__
*/




#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "interface.h"
#include "readBook.h"


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
	STstart();
	printf ("Carregando Livro.....\n");
	STstartReadBook(bookName);
	printf ("Livro Carregado.....\n");
	printf ("Insira uma opcao e palavra : ");
	fscanf (stdin,"-%s %s",opt,word);
	clear_newlines();
	while (strcmp(opt,"F") != 0){
		if (strcmp(opt,"e") == 0)
			STsearchWord(word,'e');
		if (strcmp(opt,"ev") == 0)
			STsearchWord(word,'v');
		if (strcmp(opt,"a") == 0)
			STsearchLemma(word, 'a');
		if (strcmp(opt,"av") == 0)
			STsearchLemma(word,'v');
		if (strcmp(opt,"aV") == 0)
			STannotated(word);
		
		printf ("Insira uma opcao e palavra : ");
		fscanf (stdin,"-%s %s",opt,word);
		clear_newlines();
	}
	
	printf ("Fim de Programa!\n");
	
	return 0;
}


