// $Id: undefvar.c,v 1.8 2013-04-23 18:38:50-07 - - $

//
// Illustrate the use of uninitialized variables.
// See output from valgrind.
//

#include <stdio.h>

int main (int argc, char **argv) {
   printf ("argc=%d, argv=%p, *argv=%p(%s)\n",
           argc, argv, *argv, *argv);
   int var;
   int it;
   int *p;
   if (var > 0) it = 3;
   printf ("var=%d, it=%d, p=%p\n", var, it, p);
   *p = 8;
}

//TEST// valgrind --track-origins=yes undefvar >undefvar.out 2>&1
//TEST// echo EXIT STATUS = $? >>undefvar.out
//TEST// mkpspdf undefvar.ps undefvar.c* undefvar.out*

