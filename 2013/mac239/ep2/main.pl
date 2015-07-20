#!/usr/bin/perl
#####################################################################################
#####################################################################################
use v5.10;
use strict;
use warnings;
use setOfClauses;
#####################################################################################
#####################################################################################
if (@ARGV < 1){	die "Falta arquivo de entrada!"}

my $flag = 0;
my $input;
my $output;

if ($ARGV[0] eq "-c"){ 
	$flag = 1;
	$input = $ARGV[1];
	$output = $ARGV[2];
}
else{
	$input = $ARGV[0];
	$output = $ARGV[1];
}

open INPUT, "< $input";
open OUTPUT, "> $output";

my $objeto = new setOfClauses();
#####################################################################################
#####################################################################################
while (my $line = <INPUT>){
    given($line){
		when($line =~ /^([A-Z]+):\s([0-9]+)\s([0-9]+).$/){ #Identifica variáveis e seus respetivos intervalos
		    my $variavelCapturada = $1; 	#identifica o nome da variavel
		    my $rangeList = [$2, $3]; 	#cria uma (referencia para) lista com o range da variavel
		    $objeto->addVariables($variavelCapturada, $rangeList);		#associa a variavel a seu range	
		}
		when($line =~ /^(-?[a-z]+[\(]([A-Z]+)(,\s*([A-Z]+))*[\)]\s?)+./){	#Idenfica uma clausula e seu restritor

		    my @predicates = $line =~ /(-?[a-z]+[(][A-Z,\s]+[)])+\s?/g;
		    my $predicatesList = [@predicates];
		    chomp ($line);
		    my @auxiliar = split(/\./, $line);		#separa predicados de restritores, visto que esses sao separados por ponto
		    my @restritores;
		    if (exists $auxiliar[1]){
		    	@restritores = split(",", $auxiliar[1]);		#cria um vetor em que cada elemento eh uma restricao do predicado
		    	foreach my $x (@restritores) { $x =~ s/(\s)=(\s)/$1==$2/; }		#Caso na entrada seja utilizado = troca-se para ==
		    }
		    else{
		    	@restritores = "null";
		    }
		    my $restritoresList = [@restritores];		#cria um escalar que contem a lista de restritores
		    $objeto->addPredicateList($predicatesList,$restritoresList);
		    
		}
		default{
		    die "ERRO : $line \n" ;	
		}
    }
}
close INPUT;
select OUTPUT;
# $objeto->printVariablesList();
# $objeto->printClausesList();

$objeto->writeClauses();

if (!$flag){
	$objeto->writeOutputInstances();
	close OUTPUT;
}
else{
	$objeto->writeOutputInstances();
	close OUTPUT;
	select STDOUT;
	my $output2 = $output . ".cnf";
    system("./geraCnf.pl $output $output2 ");
}


