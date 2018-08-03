//  Chris Selling
//    cselling

#include <inttypes.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "stringtable.h"

typedef struct stringtable{
   int dimension;
   int load;
   stringnode_ref* head;
} table;

typedef struct stringnode{
   cstring word;
   hashcode_t number;
} node;


table* new_stringtable(void){
   table* new = malloc(sizeof(table));
   new->dimension = 31;   // array is length 2^5 - 1, also is prime;  mod of a prime works well I'm told
   new->load = 0;
   new->head = calloc(31, sizeof(node*));   //allocate array
   return new;
}

void delete_stringtable(table* hash){
   for (int i = 0; i < hash->dimension; i++){
      if(hash->head[i] == NULL) continue;
      free(hash->head[i]->word);
      free(hash->head[i]);
   }
   free(hash);
}

void debugdump_stringtable(table* hash, FILE* filename){
   for(int i = 0; i < hash->dimension; i++){
      if(hash->head[i] == NULL) continue;
      fprintf(filename, "%8d %12u %s", i, hash->head[i]->number, hash->head[i]->word);
   }
}

hashcode_t hashFunction(cstring key){
   hashcode_t value = 0;
   for(int i = 0; (key[i]) != NULL;  i++){
      value = 31* value + key[i];
   }
   return value;
}

table* doubleArray(table* old){
   table* new = malloc(sizeof(table));
   new->dimension = (old->dimension)*2+1;
   new->load = old->load;
   new->head = calloc(new->dimension, sizeof(node));
   for(int i = 0; i < old->dimension; i++){
      if(old->head[i] == NULL) continue;
      else intern_stringtable(new, (old->head[i])->word);
   }
   delete_stringtable(old);
   return new;
}

stringnode_ref intern_stringtable(table* hash, cstring key){
   hashcode_t hashCode = hashFunction(key);
   for(int i = hashCode%(hash->dimension); (hash->head[i]) != NULL; i = (i+1)%(hash->dimension)){
      if(strcmp((hash->head[i])->word, key) == 0) return hash->head[i];
   }
   node* new = malloc(sizeof(node));
   new->number = hashCode;
   cstring newWord = calloc(strlen(key), sizeof(char));
   strcpy(newWord, key);
   new->word = newWord;
   hash->load += 1;
   if(2*(hash->load) > (hash->dimension)) hash = doubleArray(hash);
   return new;
}

cstring peek_stringtable(node* foo){
   return foo->word;
}

hashcode_t hashcode_stringtable(node* foo){
   return foo->number;
}




