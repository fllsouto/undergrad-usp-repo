#!/usr/bin/perl

use v5.10;
use FileHandle;
use strict;
use warnings;
use setOfClauses;

$, = " ;;; \n";
$" = ",,,";

if(@ARGV < 2){
    die "USO: ./geraCnf.pl <entrada> <saida>";
}

my $entrada = shift;
my $saida = shift;
my %hash;
my $count = 1;

open INPUT, "< $entrada";
open OUTPUT, "> $saida";

my @lines = <INPUT>; #cria vetor com linhas do arquivo de entrada
close INPUT;
my $numClauses = scalar  @lines; #variavel para armazenar o numero de clausulas e informalo ao SATSolver

for(@lines){
    chomp; #remove o newline (\n)
    my @clausulas = split(/\) /); #separa cada um dos termos do predicado
    my $i;
    for($i = 0; $i < @clausulas - 1; $i++){ #adiciona o parenteses removidos durante o split
	$clausulas[$i] = $clausulas[$i].")";
    }
    chop($clausulas[$i]); #remove o ponto do ultimo termo do predicado
    foreach my $word (@clausulas){
	if (index($word, "-") != -1) { #checa se a string contem o caracter "-"
	    my $key = substr $word, 1; #pega o conteudo da string sem o "-"
	    if(!exists $hash{$word}){ #verifica se a key ainda nao foi inserida no hash
		if(exists $hash{$key}){ #verifica se a versao "afirmativa" ja existe no hash
		    $hash{$word} = -$hash{$key}; #caso exista, mantem-se o mesmo nome de variavel
		}
		else{
		    $hash{$word} = -$count; #caso contrario, cria-se uma nova variavel
		    $count++;
		}
	    }
	}
	else{
	    my $neg = "-".$word; #cria a versao negada do predicado
	    if(!exists $hash{$word}){
		if(exists $hash{$neg}){
		    $hash{$word} = -$hash{$neg}; #se a versao negada ja exitir, mantem-se o mesmo nome de variavel
		}
		else{
		    $hash{$word} = $count;
		    $count++;
		}
	    }
	}
    }
    
    ####### PRINTS DE DEBUG ########
    # print "Separado: @clausulas";#
    # print "\n\n";                #
}

####### PRINTS DE DEBUG #################
#print "Hash: \n";  #
#foreach my $aux (keys %hash){          #   
#    print "$aux ------> $hash{$aux}\n";#
#}

my $numVars = 0;
foreach my $a (keys %hash){ #conta qual o maior valor de variavel, sendo esse o numero de variaveis
    if (abs($hash{$a}) > $numVars){
	$numVars = abs($hash{$a});
    }
}
select OUTPUT;
print "c Versao cnf de $entrada\n"; # cabecalho do .cnf
print "c\n";
print "p cnf $numVars $numClauses\n"; #informa ao SATSolver o numero de variaveis e de clausulas

for(@lines){
    my @clausulas = split(/\) /); #separa cada um dos termos do predicado
    my $i;
    for($i = 0; $i < @clausulas - 1; $i++){ #adiciona o parenteses removidos durante o split
	$clausulas[$i] = $clausulas[$i].")";
    }
    chop($clausulas[$i]); #remove o ponto do ultimo termo do predicado
    foreach my $word (@clausulas){
	print "$hash{$word} "; #imprime a representacao do predicado em variavel cnf
    }
    print "0\n"; #termina a disjuncao
}
