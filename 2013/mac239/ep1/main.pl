#!/usr/bin/perl

#Exercicio Programa I - Sudoku
#MAC0239 - Métodos Formais em Programacao
#Professor Marcelo Finger

#Fellipe Souto Sampaio 
#Número USP: 7990422 e-mail: fellipe.sampaio@usp.com

#Gervásio Protásio dos Santos Neto 
#Número USP: 7990996 e-mail: gervasio.neto@usp.br

#IME-USP
#2 semestre 2013


use v5.10;
use nxnArray;
use strict;
use warnings;

if(@ARGV < 3){
   die "Uso:\n./main.pl <arquivoDeEntrada> <arquivoCNF>  <arquivoRespota>\n";
}

my $input = $ARGV[0];
my $output = $ARGV[1];
my $answer = $ARGV[2];

open INPUT, "< $input";
open OUTPUT, "> $output";

my @string = split(' ', <INPUT>);# nao precisa do aspas

close INPUT;

my $mat = new nxnArray();
select OUTPUT;
$mat->readInput(@string);
$mat->insertTips();
$mat->regionExistence();
$mat->lineExistence();
$mat->columnExistence();
$mat->permuteTips();
$mat->subSquare();
$mat->highlanderLine();
$mat->highlanderColumn();
$mat->printFNC();

close OUTPUT;

if(`./minisat $output $answer`){
	system('./filtro.pl '.$answer);
}
else{
	`minisat $output $answer`;
	system('./filtro.pl '.$answer);
};



