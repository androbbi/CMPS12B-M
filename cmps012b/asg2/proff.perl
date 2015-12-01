#!/usr/bin/perl -w
# $Id: proff.perl,v 1.1 2014-02-04 15:25:56-08 - - $
#
# NAME
#    proff - run the simple jroff text formatter
#
# SYNOPSIS
#    proff [filename...]
#
# DESCRIPTION
#    Runs groff to simulate proff by using compatibility macros.
#

use strict;
use warnings;

$0 =~ s|.*/||;

my $groff = "groff -Tascii -P-bcuof";
open GROFF, "| $groff" or die "$0: $groff: $!\n";
print GROFF <DATA>;
print GROFF <>;
close GROFF;

__DATA__
.cflags 5 .?!:;
.wh 0 TP
.wh -6 BP
.de mt
.   ec
.   nr MT \\$1/2
.   eo
..
.de TP
.   ec
'   sp \\n(MT
.   tl '''%'
'   sp \\n(MT-1
.   eo
..
.de BP
.   bp
..
.hy 0
.ll 65
.pl 66
.po 10
.mt 6
.na
.eo
