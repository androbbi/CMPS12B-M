//Antony Robbins androbbi@ucsc.edu
//Brandon Gomez brlgomez@ucsc.edu
// $Id: nsort.c,v 1.1 2011-04-29 19:46:42-07 - - $
#include <assert.h>
#include <libgen.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdbool.h>

#define STDIN_NAME "-"
int exit_status = EXIT_SUCCESS;
char *prog_name = NULL;

typedef struct node node;
struct node {
   double item;
   node *link;
};

typedef struct options {
   bool print_debug;
} options;

 node *head = NULL;
void insertascending (double newitem);


void scanNum(){
   for (;;) {
      // Try to read a double number.  Print an error message if a
      // word is not recognized as a number.  Stop at end of file.
      double number;
      int scancount = scanf ("%lg", &number);
      if (scancount == EOF || scancount !=1) {
         printf ("You have reached the End of file\n");
         break;
      }else{
       insertascending(number);
      }
   };
}

void insertascending (double newitem) {
   node *prev = NULL;
   node *curr = head;
   while(curr != NULL){
     if(curr->item > newitem) break;
    prev = curr;
    curr = curr->link;
   }
   
   node *tmp = malloc (sizeof (struct node));
   assert (tmp != NULL);
   tmp->item = newitem;
   tmp->link = curr;
   if(prev == NULL) head = tmp;
         else prev->link = tmp;
}

void print_nodes(node *head, options *opts){
   if(opts->print_debug == false) {
      for(node *curr = head; curr!= NULL; curr = curr->link){
         printf("%24.15g\n", curr->item);
      }
   }
   else{
      printf ("&head= %p\n", &head);
      printf ("head= %p\n", head);
      for (node *curr = head; curr != NULL; curr = curr->link) {
         printf ("%p -> struct node {item= %.15g, link= %p}\n",
                 curr, curr->item, curr->link);
      }
      printf ("NULL= %p\n", NULL);
   }
   //Free the list after printing

   while (head != NULL) {
      node *old = head;
      head = head->link;
      free (old);
   }
 
}

void scan_options (int argc, char **argv, options *opts) {
   opts->print_debug = false;
   opterr = false;
   for (;;) {
      int opt = getopt (argc, argv, "d");
      if (opt == EOF) break;
      switch (opt) {
         case 'd':
            opts->print_debug = true;
            break;
         default:
            exit_status = EXIT_FAILURE;
            fflush (NULL);
            fprintf (stderr, "%s: -%c: invalid option\n",
                             prog_name, optopt);
            break;
      }
   }
}

int main (int argc, char **argv) { 
   options opts;
   prog_name = basename (argv[0]);
   int check = 1;
   scan_options(argc, argv, &opts);
   if(opts.print_debug == true) check = 2;
   if(argc == check){
      scanNum();
     print_nodes(head, &opts);
   }
   return exit_status;
}
