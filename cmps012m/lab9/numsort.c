//Antony Robbins androbbi@ucsc.edu
//Brandon Gomez brlgomez@ucsc.edu
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include "inssort.h"
void print (double *a, int size) {
   for(int i = 0; i < size; i++) {
      printf("%20.15g\n", a[i]);
   }
}

int dbcmp (const void *this, const void *that) {
   double *thisint = (double*) this;
   double *thatint = (double*) that;
   return (*thisint > *thatint) - (*thisint < *thatint);
   }

int main (void) {
   double array[1000];
   double num = 0;
   int count = 0;
   for(;;){
      int in = scanf("%lg", &num);
      if(in != 1 || in == EOF || count > 1000) break;
     else{
        array[count] = num;
       count++;
      }
   }
   inssort (array, count, sizeof *array, dbcmp);
   //qsort(array, count, sizeof *array, dbcmp);
   print(array, count);
   return EXIT_SUCCESS;
}
