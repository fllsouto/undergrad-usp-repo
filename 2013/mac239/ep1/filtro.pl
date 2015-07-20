#!/usr/bin/perl
use v5.10;
use strict;
use warnings;

my $input = $ARGV[0];

open INPUT, "< $input";

my $junk = <INPUT>;
my @string = split(' ',<INPUT>);

chomp (@string);
my @string2;
for (my $a = 1; $a < scalar @string; $a++) {
	if(not ($string[$a] =~ /^-[1-9]{1,3}/)){
		my $item = $string[$a];
		push (@string2,$item);

	}

}

readInput(@string2);


sub readInput{
    my @string = @_;
    my $a = 0;

    for (my $a = 0; $a < scalar @string - 1; $a++) {
    	my $waka = $string[$a] % 9;
    	if ($waka != 0) {
    		print "$waka  ";
    	} else {
    		print "9  ";
    	}
    	if ((($a+1) % 9) == 0){
    		print "\n\n";
    	}

    }

}
