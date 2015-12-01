//Antony Robbins androbbi@ucsc.edu
//Brandon Gomez brlgomez@ucsc.edu
// $Id: bigint.c,v 1.13 2014-01-24 18:33:47-08 - - $

#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bigint.h"
#include "debug.h"

#define MIN_CAPACITY 16

struct bigint {
   size_t capacity;
   size_t size;
   bool negative;
   char *digits;
};

static void trim_zeros (bigint *this) {
   while (this->size > 0) {
      size_t digitpos = this->size - 1;
      if (this->digits[digitpos] != 0) break;
      --this->size;
   }
}

bigint *new_bigint (size_t capacity) {
   bigint *this = malloc (sizeof (bigint));
   assert (this != NULL);
   this->capacity = capacity;
   this->size = 0;
   this->negative = false;
   this->digits = calloc (this->capacity, sizeof (char));
   assert (this->digits != NULL);
   DEBUGS ('b', show_bigint (this));
   return this;
}

bigint *new_string_bigint (char *string) {
   assert (string != NULL);
   size_t length = strlen (string);
   bigint *this = new_bigint (length > MIN_CAPACITY
                            ? length : MIN_CAPACITY);
   char *strdigit = &string[length - 1];
   if (*string == '_') {
      this->negative = true;
      ++string;
   }
   char *thisdigit = this->digits;
   while (strdigit >= string) {
      assert (isdigit (*strdigit));
      *thisdigit++ = *strdigit-- - '0';
   }
   this->size = thisdigit - this->digits;
   trim_zeros (this);
   DEBUGS ('b', show_bigint (this));
   return this;
}

static bigint *do_add (bigint *this, bigint *that) {
   DEBUGS ('b', show_bigint (this));
   DEBUGS ('b', show_bigint (that));
   int aCapacity = this->size > that->size ?
                 this->size +1 : that->size + 1;    
   bigint *result = new_bigint(aCapacity);
   assert(result != NULL);
   if(this->digits > that->digits)
      result->negative = that->negative;
   else
      result->negative = this->negative;
   int digit = 0;
   int carry = 0;
   for(int i = 0; i < aCapacity; i++){
      digit = this->digits[i] + that->digits[i] + carry;
     result->digits[i] = digit % 10;
     carry = digit / 10;
     result->size++;
   }
   trim_zeros(result);
   return result;
}

static bigint *do_sub (bigint *this, bigint *that) {
   DEBUGS ('b', show_bigint (this));
   DEBUGS ('b', show_bigint (that));
   int sCapacity = this->size;
   bigint *result = new_bigint(sCapacity);
   assert(result != NULL);
   result->negative = this->negative;
   int digit = 0;
   int borrow = 0;
   for(int i = 0; i < sCapacity; i++) {
      digit = this->digits[i] - that->digits[i] - borrow + 10;
     result->digits[i] = digit % 10;
     borrow = 1 - digit / 10;
     result->size++;
   }
   trim_zeros(result);
   return result;
}
void free_bigint (bigint *this) {
   free (this->digits);
   free (this);
}

void print_bigint (bigint *this, FILE *file) {
   DEBUGS ('b', show_bigint (this));
   if(this->negative == true)
      fprintf(file, "-");
   for(int i = this->size; i >=0; i--)
      fprintf(file, "%d", this->digits[i]);
   printf("\n");
}

bigint *add_bigint (bigint *this, bigint *that) {
   DEBUGS ('b', show_bigint (this));
   DEBUGS ('b', show_bigint (that));
   if(this->negative == that->negative)
      return do_add(this, that);
   else{
      if(this->digits > that->digits)
         return do_sub(this, that);
      else
         return do_sub(that, this);
   } 
}

bigint *sub_bigint (bigint *this, bigint *that) {
   DEBUGS ('b', show_bigint (this));
   DEBUGS ('b', show_bigint (that));
   if(this->negative != that->negative)
      return do_add(this, that);
   else{
      if(this->digits > that->digits)
         return do_sub(this, that);
      else
         return do_sub(that, this);
   }
}


bigint *mul_bigint (bigint *this, bigint *that) {
   DEBUGS ('b', show_bigint (this));
   DEBUGS ('b', show_bigint (that));
   int left = this->size;
   int right = that->size;
   int capacity = left + right;
   bigint *product = new_bigint(capacity);
   for(int i = 0; i < left; i++){
      int carry = 0;
      for(int j = 0; j < right; j++){
         int digit = product->digits[i+j] + 
        this->digits[i] * that->digits[j] + carry;
        product->digits[i+j] = digit % 10;
        carry = digit / 10;
      }
      product->digits[i+that->size] = carry;
     product->size++;
    }
   return product;
}

void show_bigint (bigint *this) {
   fprintf (stderr, "bigint@%p->{%lu,%lu,%c,%p->", this,
            this->capacity, this->size, this->negative ? '-' : '+',
            this->digits);
   for (char *byte = &this->digits[this->size - 1];
        byte >= this->digits; --byte) {
      fprintf (stderr, "%d", *byte);
   }
   fprintf (stderr, "}\n");
}

