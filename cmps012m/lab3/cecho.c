// $Id: cecho.c,v 1.2 2013-09-25 14:21:04-07 - - $
//
// NAME
//    cecho - echo command line arguments to stdout
//
// SYNOPSIS
//    cecho [arguments...]
//
// DESCRIPTION
//    The command line arguments are echoed to stdout, separated
//    by spaces and terminated by a newline.
//

#include <stdio.h>
#include <stdlib.h>

int main (int argc, char **argv) {
   for (int argi = 1; argi < argc; ++argi) {
      if (argi > 1) printf (" ");
      printf ("%s", argv[argi]);
   }
   printf ("\n");
   return EXIT_SUCCESS;
}

//TEST// ./cecho hello world and goodbye >cecho.lis 2>&1
//TEST// mkpspdf cecho.ps cecho.c* cecho.lis

