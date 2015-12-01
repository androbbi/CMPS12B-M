// $Id: getoptex.c,v 1.8 2013-04-24 21:03:46-07 - - $
// Antony Robbins androbbi@ucsc.edu
// Brandon Gomez brlgomez@ucsc.edu

//
// NAME
//    getoptex - getopt(3) example
//
// SYNOPSIS
//    getoptex [-ilm] operands
//
// DESCRIPTION
//    An example to show now getopt(3) is used.  After scanning
//    options, all options and operands are printed.
//

#include <libgen.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

char *program_name = NULL;
int exit_status = EXIT_SUCCESS;

typedef struct options {
   bool ignore_case;
   bool filenames_only;
   bool number_lines;
} options;

void scan_options (int argc, char **argv, options *opts) {
   opts->ignore_case = false;
   opts->filenames_only = false;
   opts->number_lines = false;
   opterr = false;
   for (;;) {
      int opt = getopt (argc, argv, "ilm");
      if (opt == EOF) break;
      switch (opt) {
         case 'i':
            opts->ignore_case = true;
            break;
         case 'l':
            opts->filenames_only = true;
            break;
         case 'm':
            opts->number_lines = true;
            break;
         default:
            exit_status = EXIT_FAILURE;
            fflush (NULL);
            fprintf (stderr, "%s: -%c: invalid option\n",
                             program_name, optopt);
            break;
      }
   }
}


const char *strbool (bool value) {
   return value ? "true" : "false";
}

int main (int argc, char **argv) {
   options opts;
   program_name = basename (argv[0]);
   scan_options (argc, argv, &opts);
   printf ("ignore_case = %s\n", strbool (opts.ignore_case));
   printf ("filenames_only = %s\n", strbool (opts.filenames_only));
   printf ("number_lines = %s\n", strbool (opts.number_lines));
   for (int argi = optind; argi < argc; ++argi) {
      printf ("operand[%d] = \"%s\"\n", argi, argv[argi]);
   }
   return exit_status;
}

//TEST// ./getoptex -im foo bar baz >getoptex.out
//TEST// mkpspdf getoptex.ps getoptex.c* getoptex.out*

