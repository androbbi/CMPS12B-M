#!/usr/bin/perl
# $Id: pmatch.perl,v 1.4 2013-02-05 11:33:55-08 - - $

use strict;
use warnings;
use Getopt::Std;

$0 =~ s|^.*/||;
my $exit_status = 0;
END {exit $exit_status}
sub note(@) {print STDERR "$0: @_"};
$SIG{'__WARN__'} = sub {note @_; $exit_status = 1};
$SIG{'__DIE__'} = sub {warn @_; exit};

my %opts;
getopts "iln", \%opts;
print STDERR "Usage: $0 [-iln] string [filename...]\n"
      and $exit_status = 1 and exit
      unless @ARGV > 0;
my $string = shift @ARGV;

push @ARGV, "-" unless @ARGV;
for my $filename (@ARGV) {
   open my $file, "<$filename" or warn "$filename: $!\n" and next;
   my $filematched;
   for (my $linenr = 1; defined (my $line = <$file>); ++$linenr) {
      my $matched = $opts{"i"} ? index (lc $line, lc $string) >= 0
                               : index ($line, $string) >= 0;
      if ($matched) {
         $filematched = 1;
         unless ($opts{"l"}) {
            print "$filename:" if @ARGV > 1;
            print "$linenr:" if $opts{"n"};
            print $line;
         }
      }
   }
   print "$filename\n" if $opts{"l"} and $filematched;
   close $file;
}

