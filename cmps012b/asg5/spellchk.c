//Antony Robbins androbbi@ucsc.edu
//Brandon Gomez brlgomez@ucsc.edu
// $Id: spellchk.c,v 1.7 2014-03-05 19:24:07-08 - - $

#include <errno.h>
#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "debugf.h"
#include "hashset.h"
#include "yyextern.h"

#define STDIN_NAME       "-"
#define DEFAULT_DICTNAME \
        "/afs/cats.ucsc.edu/courses/cmps012b-wm/usr/dict/words"
#define DEFAULT_DICT_POS 0
#define EXTRA_DICT_POS   1
#define NUMBER_DICTS     2

void print_error (const char *object, const char *message) {
  fflush (NULL);
  fprintf (stderr, "%s: %s: %s\n", Exec_Name, object, message);
  fflush (NULL);
  Exit_Status = EXIT_FAILURE;
}

FILE *open_infile (const char *filename) {
  FILE *file = fopen (filename, "r");
  if (file == NULL) print_error (filename, strerror (errno));
  DEBUGF ('m', "filename = \"%s\", file = 0x%p\n", filename, file);
  return file;
}

void spellcheck (const char *filename, hashset *hashset) {
  yylineno = 1;
  DEBUGF ('m', "filename = \"%s\", hashset = 0x%p\n",
     filename, hashset);
  for (;;) {
    int token = yylex ();
    if (token == 0) break;
    DEBUGF ('m', "line %d, yytext = \"%s\"\n", yylineno, yytext);
    if (has_hashset(hashset, yytext)) continue;
    else{
      printf("%s: %d: %s\n",filename, yylineno, yytext);
      Exit_Status = EXTRA_DICT_POS;
   }
  }
   
}

void load_dictionary (const char *dictionary_name, hashset *hashset) {
  if (dictionary_name == NULL) return;
  DEBUGF ('m', "dictionary_name = \"%s\", hashset = %p\n",
     dictionary_name, hashset);
  char buffer[1024];
  FILE *dictionary = open_infile(dictionary_name);
  while(fgets(buffer, sizeof buffer, dictionary) != NULL){
    char *n1 = strchr (buffer, '\n');
    if(n1 != NULL) *n1 = '\0';
    char *string = strdup(buffer);
    put_hashset(hashset, string);
   free(string);
  }
  fclose(dictionary);
}


int main (int argc, char **argv) {
  Exec_Name = basename (argv[0]);
  char *default_dictionary = DEFAULT_DICTNAME;
  char *user_dictionary = NULL;
  hashset *hashset = new_hashset ();
  yy_flex_debug = false;

  // Scan the arguments and set flags.
  opterr = false;
  for (;;) {
    int option = getopt (argc, argv, "nxyd:@:");
    if (option == EOF) break;
    switch (option) {
      char optopt_string[16]; // used in default:
    case 'd': user_dictionary = optarg;
      break;
    case 'n': default_dictionary = NULL;
      break;
    case 'x': STUBPRINTF ("-x\n");
      break;
    case 'y': yy_flex_debug = true;
      break;
    case '@': set_debugflags (optarg);
      if (strpbrk (optarg, "@y")) yy_flex_debug = true;
      break;
    default : sprintf (optopt_string, "-%c", optopt);
      print_error (optopt_string, "invalid option");
      break;
    }
  }

  // Load the dictionaries into the hash table.
  load_dictionary (default_dictionary, hashset);
  load_dictionary (user_dictionary, hashset);

  // Read and do spell checking on each of the files.
  if (optind >= argc) {
    yyin = stdin;
    spellcheck (STDIN_NAME, hashset);
  }else {
    for (int fileix = optind; fileix < argc; ++fileix) {
      DEBUGF ('m', "argv[%d] = \"%s\"\n", fileix, argv[fileix]);
      char *filename = argv[fileix];
      if (strcmp (filename, STDIN_NAME) == 0) {
   yyin = stdin;
   spellcheck (STDIN_NAME, hashset);
      }else {
   yyin = open_infile (filename);
   if (yyin == NULL) continue;
   spellcheck (filename, hashset);
   fclose (yyin);
      }
    }
  }
   
  yylex_destroy ();
  free_hashset(hashset);
  return Exit_Status;
}
