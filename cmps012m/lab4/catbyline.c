// $Id: catbyline.c,v 1.5 2014-01-28 17:59:24-08 - - $

//
// NAME
//    catbyline - example of simple cat to display files
//
// SYNOPSIS
//    catbyline [filename...]
//
// DESCRIPTION
//    Uses fgets to read lines from files and prints to stdout.
//    If no filenames are specified, reads stdin.
//    Does not consider whether input buffer is too short.
//

#include <errno.h>
#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *program_name = NULL;
int exit_status = EXIT_SUCCESS;
#define STDIN_NAME "-"

void catbyline (FILE *input, char *filename) {
   char buffer[1024];
   printf ("FILE %s:\n", filename);
   for (int linenr = 1;; ++linenr) {
      char *buf = fgets (buffer, sizeof buffer, input);
      if (buf == NULL) break;
      printf ("%6d: %s", linenr, buf);
   }
}


int main (int argc, char **argv) {
   program_name = basename (argv[0]);
   if (argc == 1) {
      catbyline (stdin, STDIN_NAME);
   }else {
      for (int argi = 1; argi < argc; ++argi) {
         char *filename = argv[argi];
         if (strcmp (filename, STDIN_NAME) == 0) {
            catbyline (stdin, STDIN_NAME);
         }else {
            FILE *input = fopen (filename, "r");
            if (input != NULL) {
               catbyline (input, filename);
               fclose (input);
            }else {
               exit_status = EXIT_FAILURE;
               fflush (NULL);
               fprintf (stderr, "%s: %s: %s\n", program_name,
                        filename, strerror (errno));
               fflush (NULL);
            }
         }
      }
   }
   return exit_status;
}

//TEST// cal 9 1752 >cal.1752.09; cal 4 2013 >cal.2013.04
//TEST// catbyline cal.1752.09 cal.2013.04 >catbyline.out
//TEST// mkpspdf catbyline.ps catbyline.c* catbyline.out*

