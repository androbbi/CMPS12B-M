//Antony Robbins androbbi@ucsc.edu
//Brandon Gomez brlgomez@ucsc.edu
// $Id: hashset.c,v 1.8 2014-03-05 19:24:07-08 - - $

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "debugf.h"
#include "hashset.h"
#include "strhash.h"

#define HASH_NEW_SIZE 15

typedef struct hashnode hashnode;
struct hashnode {
  char *word;
  hashnode *link;
};

struct hashset {
  size_t size;
  size_t load;
  hashnode **chains;
};

hashset *new_hashset (void) {
  hashset *this = malloc (sizeof (struct hashset));
  assert (this != NULL);
  this->size = HASH_NEW_SIZE;
  this->load = 0;
  size_t sizeof_chains = this->size * sizeof (hashnode *);
  this->chains = malloc (sizeof_chains);
  assert (this->chains != NULL);
  memset (this->chains, 0, sizeof_chains);
  DEBUGF ('h', "%p -> struct hashset {size = %d, chains=%p}\n",
     this, this->size, this->chains);
  return this;
}

void free_hashset (hashset *this) {
  hashnode *t = NULL;
  hashnode *temp = NULL; 
  DEBUGF ('h', "free (%p)\n", this);
  for(int i = 0; i < (int)this->size; i++){
  temp = this->chains[i];
    while(temp != NULL){
      t = temp;
      temp = temp->link;
      free(t->word);
      free(t);
    }
  }
  free(this->chains);
  free(this);
   
}

void put_hashset (hashset *this, const char *item) {
  hashnode *h = malloc(sizeof(hashnode));
  assert(h != NULL);
  int index = strhash(item) % this->size;
  h->word = strdup(item);
  h->link = this->chains[index];
  this->chains[index] = h;
  this->load++;
}

bool has_hashset (hashset *this, const char *item) {
  size_t index = strhash (item) % this->size;
  for(hashnode *curr = this->chains[index]; curr != NULL; curr = curr->link){
    if(strcmp (curr->word, item) == 0){
      return true;
    }
  }
  return false;
}

void double_hashset(hashset *this){
   size_t size = this->size;
   size_t double_size = (2 * size) + 1;
   hashnode **new = malloc(double_size * sizeof(hashnode *));
   assert (new != NULL);
   for(int i = 0; i < (int)double_size; i++) {
      new[i] = NULL;
   }
   for (int i = 0; i < (int)size; i++){
      while(this->chains[i] != NULL) {
        hashnode *curr = this->chains[i];
         size_t index = strhash(curr->word) % double_size;
       curr->link = new[index];
       new[index] = curr;
       this->chains[i] = curr->link;
      }
   }
   hashnode **t = this->chains;
   this->chains = new;
   free(t);
}
