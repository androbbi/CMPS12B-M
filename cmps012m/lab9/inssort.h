//Antony Robbins androbbi@ucsc.edu
//Brandon Gomez brlgomez@ucsc.edu
#ifndef _INSSORT_H__
#define _INSSORT_H__

void inssort (void *base, size_t nelem, size_t size,
         int(*compar) (const void*, const void*));
#endif
