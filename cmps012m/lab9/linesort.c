//Antony Robbins androbbi@ucsc.edu
//Brandon Gomez brlgomez@ucsc.edu
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "inssort.h"

void print(char** sentence, int size){
   for(int i = 0; i < size; i++) {
      printf("%s\n", sentence[i]);
     free(sentence[i]);
   }
}


int strstrcmp (const void *this, const void *that) {
   char **thisstr = (char**) this;
   char **thatstr = (char**) that;
   return strcmp (*thisstr, *thatstr);
}

int main(void) {
   char buffer[1000];
   char *point[1000];
   int count = 0;
   for(;;){
      int in = scanf("%s", buffer); 
      if (in == EOF || count > 1000) break;
      else{
         point[count] = strdup(buffer);
       count++;
       //if(point[count] == '\0') point[count] = '\n';
      }
   }
   inssort (point, count, sizeof *point, strstrcmp);
   //qsort(point, count, sizeof *point, strstrcmp);
   print(point, count);
   return EXIT_SUCCESS;
}
