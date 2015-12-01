//Antony Robbins androbbi@ucsc.edu
//Brandon Gomez brlgomez@ucsc.edu
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

#include "inssort.h"

void inssort( void *base, size_t nelem, size_t size,
         int (*compar) (const void *, const void *)){
   for(size_t i = 1; i < nelem; ++i){
      int slot = i;
     void* element = malloc(size);
     memcpy(element, (char*)(base + slot * size), size);
     
     for(; slot > 0; --slot){
        int compare = 0;
       compare = (*compar) (element, base + ((slot-1) *size));
       if(compare > 0) break;
       else{
          void *tmp = (char*) base + size * slot;
         memcpy(tmp,(char*) base + (slot -1) * size, size);
         }
      }
     memcpy((char*)(base + slot * size), element, size);
     free(element);
   }
}
