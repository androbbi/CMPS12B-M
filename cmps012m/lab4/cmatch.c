//Antony Robbins androbbi
//Brandon Gomez brlgomez

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdbool.h>

#define STDIN_NAME "-"
char *program_name = NULL;
int exit_status = EXIT_SUCCESS;

typedef struct options {
   bool ignore_case;
   bool filenames_only;
   bool number_lines;
} options;

void cmatch(FILE *input, char *filename,
               char *needle, options *opts, int multi){
   char buffer[1024];
   for (int linenr = 1;; ++linenr) {
      char *buf = fgets (buffer, sizeof buffer, input);
      if(buf == NULL) break;
      if(opts->ignore_case == true && opts->number_lines == false
             && opts->filenames_only == false){
         if(strcasestr(buf, needle) != NULL && multi == 0)
            printf ("%s", buf); 
         if(strcasestr(buf, needle) != NULL && multi > 0)
            printf ("%s:%s",filename, buf);
      }
      if(opts->ignore_case == true && opts->number_lines == true
              && opts->filenames_only == false){
         if(strcasestr(buf, needle) != NULL && multi == 0)
            printf ("%2d: %s", linenr, buf);
         if(strcasestr(buf, needle) != NULL && multi > 0)
            printf ("%s:%2d:%s",filename, linenr, buf);  
      }
      if(opts->ignore_case == true && opts->number_lines == false
              && opts->filenames_only == true){
         if(strcasestr(buf, needle) != NULL){
            printf ("%s\n", filename);
            return;
         }
      }
      if(opts->ignore_case == true && opts->number_lines == true
              && opts->filenames_only == true){
         if(strcasestr(buf, needle) != NULL){
            printf ("%s\n", filename);
            return;
         }
      }
      if(opts->ignore_case == false && opts->number_lines == true
             && opts->filenames_only == false){
         if(strstr(buf, needle) != NULL && multi == 0)
            printf ("%2d: %s", linenr, buf);
         if(strstr(buf, needle) != NULL && multi > 0)
            printf ("%s:%2d:%s",filename, linenr, buf);   
      }
       if(opts->ignore_case == false && opts->number_lines == true
               && opts->filenames_only == true){
         if(strstr(buf, needle) != NULL){
            printf ("%s\n", filename);
            return;
         }
      }
      if(opts->ignore_case == false && opts->number_lines == false
              && opts->filenames_only == true){
         if(strstr(buf, needle) != NULL){
            printf ("%s\n", filename);
            return;
         }
     }
      if(opts->ignore_case == false && opts->number_lines == false
              && opts->filenames_only == false){
         if(strstr(buf, needle) != NULL && multi == 0)
            printf ("%s", buf);
         if(strstr(buf, needle) != NULL && multi > 0)
            printf ("%s:%s",filename, buf);
     }
  }
}

void scan_options (int argc, char **argv, options *opts) {
   opts->ignore_case = false;
   opts->filenames_only = false;
   opts->number_lines = false;
   opterr = false;
   for (;;) {
      int opt = getopt (argc, argv, "iln");
      if (opt == EOF) break;
      switch (opt) {
         case 'i':
            opts->ignore_case = true;
            break;
         case 'l':
            opts->filenames_only = true;
            break;
         case 'n':
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
int main(int argc, char **argv){
   options opts;
   int check = 1;
   int multi = 0;
   //program_name = basename (argv[0]);
   //If the input line is empty
   //Read in Standard input
   if (argc < 3) {
      fprintf (stderr,"%s\n","Usage:[-iln] string [filename...]"); 
   }
   else {
      scan_options(argc, argv, &opts);
      if(opts.ignore_case == true || opts.number_lines == true
             || opts.filenames_only == true) {
         check = 2;
      }
      char *needle = argv[check];
      for (int argi = 1; argi < argc; ++argi) {
         //Reads in the options
         if(argi > check){  
            char *filename = argv[argi];
            //If - is inputed
            //Take in standard input
            if (strcmp (filename, STDIN_NAME) == 0) {
               cmatch (stdin, STDIN_NAME, needle, &opts, multi);
               //If its a file name
               //Read in the file
            }else {
               FILE *input = fopen (filename, "r");
               //If there is actual input
               //Read the file
               if (input != NULL) {
                  cmatch (input, filename, needle, &opts, multi);
                  fclose (input);
               }else {
                  //If the file is empty
                  //Print error message
                  exit_status = EXIT_FAILURE;
                  fflush (NULL);
                  fprintf (stderr, "%s: %s: %s\n", program_name,
                           filename, strerror (errno));
                  fflush (NULL);
               }
            }
            multi++;
         }
      }
   }
   return exit_status;
}
