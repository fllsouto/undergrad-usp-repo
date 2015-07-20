#!/usr/bin/perl

use v5.10;
use strict;
use warnings;

my $text = "foo bar";
print "Texto :" .$text ."\n";
# if ($text =~/^([A-Z]+):\s([0-9]+)\s([0-9]+).$/){
# 	print "Sucesso!\n";
# 	print "Variavel : $1\n";
# 	print "Range : ($2 ~ $3)\n";
# }else{
# 	print "Deu Errado!";
# }

# if($text =~/^(-?[a-z]+[\(]([A-Z]+)(,\s[A-Z]+)*?[\)]\s)+.$/){
# 	print "Sucesso!\n";
# }else{
# 	print "Deu Errado!";
# }


# if($text =~/^.\s([A-Z]+)(\s[\+\-\*\/]\s[A-Z]+)+?.$/){
# 	print "Sucesso!\n";
# }else{
# 	print "Deu Errado!\n";
# }
# if($text =~/^.((\s([A-Z]+)(\s[\+\-\*\/]\s[A-Z]+)+?)\s(<|>|>=|<=|==|!=)(\s([A-Z]+)(\s[\+\-\*\/]\s[A-Z]+)+?))+.$/){

# if($text =~/^[\.]((\s([A-Z]+)(\s(\+|\-|\*|\/)\s[A-Z]+)*\s(<|>|>=|<=|==|!=)\s([A-Z]+)(\s(\+|\-|\*|\/)\s[A-Z]+)*)*[\.])?$/){
# 	print "Sucesso!\n";
# }else{
# 	print "Deu Errado!\n";
# }

if($text =~ /[a-z]/ ){
	my @list = $text =~ /([a-z]+)+/g;
	print "Value : @list";
}
# if($text =~/^([-]?[a-z]+[\(]([A-Z]+)(,\s[A-Z]+)*?[\)]\s)+$/){
