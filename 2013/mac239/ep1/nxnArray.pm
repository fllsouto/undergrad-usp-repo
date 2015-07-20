#!/usr/bin/perl

use v5.10;
use strict;
use warnings;

package nxnArray;

#Construtor da Classe
sub new{
    my $class = shift;
    my $self = {
	sudoku => [],
	FNC => {},
	input => [],
	qntClausules => 0,
	centros => [[1,1],[1,4],[1,7],[4,1],[4,4],[4,7],[7,1],[7,4],[7,7]]
    };

    bless $self, $class;
    return $self;
}



#imprime a matrix criada
sub printMatrix{
    my $self = shift;
    my $index = shift;
    print "Aqui #$index\n\n";
    for(my $i = 0; $i < 9; $i++){
	for(my $j = 0; $j < 9; $j++){
	    print "$self->{$index}[$i][$j] ";
	}
	print "\n";
    }
    print "\n";
}

#constroi o sudoku
sub readInput{
    my $self = shift;
    #Facepalm!
    my @string = @_;
    $self->{input} = \@string;
    my $a = undef;
    my $i = 0;
    my $j = 0;

    use integer;
    for($a = 0; $a < 81; $a++,$j++){
		if($j == 9){
		    $j = 0;
		    $i++;
		}
		$self->{sudoku}[$i][$j] = $string[$a];
    }

}

#dado um a e um indx retorna sua equivalencia
sub tipReturn {
    my $a = shift;
    my $indx = shift;

    return 9*$a +$indx;
}
#Insere as Dicas
sub insertTips{
	my $self = shift;
	my $tipCounter = 0;
	for (my $a = 0; $a < 81; $a++) {
		if ($self->{input}[$a] != 0){
			my $v = tipReturn($a,$self->{input}[$a]);
			my $claus = $v." 0";
			insertClausule($self,$claus);
		}
	}
}
#Permuta os candidatos de um quadrado
sub permuteTips{
	my $self = shift;
	for (my $a = 0; $a < 81; $a++) {
		for (my $b = 1; $b <= 9; $b++) {
			for (my $c = $b + 1; $c <= 9; $c++) {
				my $tip1 = tipReturn($a,$b);
				my $tip2 = tipReturn($a,$c);
				my $claus = "-".$tip1." -".$tip2." 0";
				insertClausule($self,$claus);
			}
			
		}
	}
}
#Insere as clausulas na tabela de hashing
sub insertClausule{
	my $self = shift;
	my $clausule = shift;
	if (not (exists $self->{FNC}{$clausule})){
		$self->{FNC}{$clausule} = 1;
		$self->{qntClausules}++;
	}
}
#Imprime as clausulas
sub printFNC{
	my $self = shift;
	print "c Sudoku\nc\np cnf 729 $self->{qntClausules}\n";
	my @clausules = keys % {$self->{FNC}};
	foreach my $key (@clausules) {
		print "$key\n";
	}
}

#Metodo do subquadrado
sub subSquare {
    my $self = shift;
    use integer;

    for (my $z = 0; $z < 9; $z++) {
	
		for(my $c = 0; $c < 9; $c++){
		    my $l = $self->{centros}->[$c]->[0];
		    my $k = $self->{centros}->[$c]->[1];

		    for(my $p = -1; $p <= 1; $p++){
				for(my $q = -1; $q <= 1; $q++){
				    my $fixo = 9*($l+$p) + 81*($k+$q) + $z;
				    for(my $m = -1; $m <= 1; $m++){
						for(my $n = -1; $n <= 1; $n++){		
						    my $comb = 9*($l+$m) + 81*($k+$n) +$z;
						    if( ($m > $p) || ($m == $p && $n > $q) ){
							    my $claus = "-".($fixo+1)." -".($comb+1)." 0";
								insertClausule($self,$claus);

							}
						}	
				    }	
				    
				}

		    }
		}

    }
}
#Metodo das linhas
sub highlanderLine {
    my $self = shift;
    for (my $z = 0; $z < 9; $z++) {
	for (my $i = 0; $i < 9; $i++) {
	    for (my $j = 0; $j < 9; $j++) {
			my $fixo = 9*($j) + 81*($i) + $z; 
			for (my $k = $j +1; $k < 9; $k++) {
			    my $comb = 9*($k) + 81*($i) +$z;
			    my $claus = "-".($fixo+1)." -".($comb+1)." 0";
				insertClausule($self,$claus);
			}
	    }
	}
    }
    
}
#Metodo das colunas
sub highlanderColumn {
    my $self = shift;
    for (my $z = 0; $z < 9; $z++) {
	for (my $j = 0; $j < 9; $j++) {
	    for (my $i = 0; $i < 9; $i++) {
			my $fixo = 9*($j) + 81*($i) + $z; 
			for (my $k = $i +1; $k < 9; $k++) {
			    my $comb = 9*($j) + 81*($k) +$z;
			    my $claus = "-".($fixo+1)." -".($comb+1)." 0";
				insertClausule($self,$claus);
			}
	    }
	}
    }
    
}
#Existencia das colunas
sub columnExistence{
    my $self = shift;
    my $longClausule = undef;
    for (my $z = 0; $z < 9; $z++) {
		for (my $j = 0; $j < 9; $j++) {
		    for (my $i = 0; $i < 9; $i++) {
				my $fixo = 9*($j) + 81*($i) + $z + 1;
				$longClausule = $longClausule."$fixo ";
			}
			$longClausule = $longClausule." 0";
		    insertClausule($self,$longClausule);
		    $longClausule = undef;
		}
    }
}
#Existencia das regioes
sub regionExistence{
    my $self = shift;
    my $longClausule = 	undef;
    use integer;

    for(my $z = 0; $z < 9; $z++){
		for(my $c = 0; $c < 9; $c++){
		    my $l = $self->{centros}->[$c]->[0];
		    my $k = $self->{centros}->[$c]->[1];
		    for(my $p = -1; $p <= 1; $p++){
				for(my $q = -1; $q <= 1; $q++){
				    my $fixo = 9*($l+$p) + 81*($k+$q) + $z + 1;
					$longClausule = $longClausule."$fixo ";
				}
		    }
		    $longClausule = $longClausule." 0";
		    insertClausule($self,$longClausule);
		    $longClausule = undef;
		}
    }
}
#Existencia das linhas
sub lineExistence{
    my $self = shift;
    my $longClausule = undef;
    for (my $z = 0; $z < 9; $z++) {
		for (my $i = 0; $i < 9; $i++) {
		    for (my $j = 0; $j < 9; $j++) {
				my $fixo = 9*($j) + 81*($i) + $z +1;
				$longClausule = $longClausule."$fixo ";
			}
			$longClausule = $longClausule." 0";
		    insertClausule($self,$longClausule);
		    $longClausule = undef;
		}
    }
}
1;
