// $Id: catbychar.c,v 1.5 2014-01-28 17:59:24-08 - - $

//
// NAME
//    catbychar - example of simple cat to display files
//
// SYNOPSIS
//    catbychar [filename...]
//
// DESCRIPTION
//    Uses fgetc(3) to read bytes from files.
//    If no filenames are specified, reads stdin.
//

#include <errno.h>
#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STDIN_NAME "-"
char *program_name = NULL;
int exit_status = EXIT_SUCCESS;

void catbychar (FILE *input, char *filename) {
   printf ("FILE %s:\n", filename);
   for (;;) {
      int byte = fgetc (input);
      if (byte == EOF) break;
      putchar (byte);
   }
}


int main (int argc, char **argv) {
   program_name = basename (argv[0]);
   if (argc == 1) {
      catbychar (stdin, STDIN_NAME);
   }else {
      for (int argi = 1; argi < argc; ++argi) {
         char *filename = argv[argi];
         if (strcmp (filename, STDIN_NAME) == 0) {
            catbychar (stdin, STDIN_NAME);
         }else {
            FILE *input = fopen (filename, "r");
            if (input != NULL) {
               catbychar (input, filename);
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

//TEST// ls -bgoa | catbychar >catbychar.out
//TEST// mkpspdf catbychar.ps catbychar.c* catbychar.out*

