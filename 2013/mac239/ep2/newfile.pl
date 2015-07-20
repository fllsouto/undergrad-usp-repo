#!/usr/bin/perl
use v5.10;
#use strict;
#use warnings;
# $a = <>;

# eval {
# 	eval($a)
# };
# if ($@) {
# 	printf "You make a mistake";
# }

# sub make_saying {
# 	my $salute = shift;
# 	my $newfunc = sub {
# 		my $target = shift;
# 		say "$salute, $target!";
# 	};
# 	return $newfunc;
# }

# $f = make_saying("Wakaka");
# $g = make_saying("Greetings");
# $f->("bar");
# $g->("earthlings");

printf "Insira X : ";
chomp($x = <STDIN>);
printf "Insira Y : ";
chomp( $y = <STDIN>);
printf "Valor ($x, $y)\n";

sub make_process{
	my $closure = sub{
		my $x = shift;
		my $y = shift;
		$result = eval $exp;
		if($result){printf "\nTRUE\n";}
		else{printf "\nFALSE\n";}
			
	};

	return $closure;
}
printf "Insira o comparador : ";
chomp($signal = <STDIN>);

given ($signal){
	when(/==/i){$exp = "$x ". $signal ." $y";}
	when(/>/i){$exp = "$x ". $signal ." $y";}
	when(/</i){$exp = "$x ". $signal ." $y";}
	when(/>=/i){$exp = "$x ". $signal ." $y";}
	when(/<=/i){$exp = "$x ". $signal ." $y";}
	when(/!=/i){$exp = "$x ". $signal ." $y";}
	default{
		printf "Wrong Binary operator!\n";
		exit;
	}
}
# printf "\nSignal : $exp\n"
$f = make_process($exp);
$f->($x,$y);



