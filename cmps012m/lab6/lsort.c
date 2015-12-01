//Antony Robbins androbbi@ucsc.edu
//Brandon Gomez brlgomez@ucsc.edu
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
   char *item;
   node *link;
};

typedef struct options {
   bool print_debug;
} options;

node *head = NULL;
void insertascending (char *newitem);


void scanString(){
   for (;;) {
       char buffer[82];
       char *r = fgets(buffer, sizeof buffer, stdin);
       if(r != NULL){
            insertascending(r);
       }else{
         printf("You have reached the End of file\n");
         break;
         }
   };
}

void insertascending (char *newitem) {
   node *prev = NULL;
   node *curr = head;
   while(curr != NULL){
      int num = strcmp(curr->item, newitem);
      if(num > 0) break;
      prev = curr;
      curr = curr->link;
   }

   node *tmp = malloc (sizeof (struct node));
   assert (tmp != NULL);
   tmp->item = strdup(newitem);
   assert(tmp->item);
   tmp->link = curr;
   if(prev == NULL) head = tmp;
   else prev->link = tmp;
}

void print_nodes(node *head, options *opts){
   if(opts->print_debug == false) {
      for(node *curr = head; curr!= NULL; curr = curr->link){
         printf("%s", curr->item);
      }
   }
   else{
      printf ("&head= %p\n", &head);
      printf ("head= %p\n", head);
      for (node *curr = head; curr != NULL; curr = curr->link) {
         printf ("%p -> struct node {item= %s, link= %p}",
               curr, curr->item, curr->link);
      }
      printf ("NULL= %p\n", NULL);
   }
   while (head != NULL) {
      node *old = head;
     char *oldstr = head->item;
      head = head->link;
     free (oldstr);
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
      scanString();
      print_nodes(head, &opts);
   }
   return exit_status;
}
