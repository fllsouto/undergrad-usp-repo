#!/usr/bin/perl
use strict;
my $String = 'foo(X, Y) -bar(Y, Z,W) -waka(XYCARA)';
print "$String\n";
my $var = "Y";
my $val = "5";
$String =~ s/$var([,|\)])/$val$1/g;
print $String."\n";

