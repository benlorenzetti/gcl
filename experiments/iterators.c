#define ARRAY_SIZE 1000
#include <stdlib.h>
#include "lor_unique_compiler_string.h"

typedef struct lor_iterator_random_access_struct {
  void* iter;
  void* (*const next)(void*);
  void* (*const prev)(void*);
  void* (*const advance)(void*, unsigned int);
} lor_iterator_random_access_t;

typedef struct lor_iterator_forward_struct {
  void* iter;
  void* (*const next)(void*);
} lor_iterator_forward_t;

#define LOR_ITERATOR_NEW_RANDOM_ACCESS_TYPE(type) \
static void* type##_array_next(void *ptr) { \
  return ptr += sizeof(type); \
} \
static void* type##_array_prev(void *ptr) { \
  return ptr -= sizeof(type); \
} \
static void* type##_advance(void *ptr, unsigned int dist) { \
  return ptr += dist * sizeof(type); \
}

#define LOR_ITERATOR_NEW_FORWARD_ITERATOR_TYPE_HELPER(type, unique_str) \
struct type##_forward_list_##unique_str { \
  type val; \
  type *next; \
}; \
static void* type##_next(void *ptr) { \
  return ((struct type##_forward_list_##unique_str *)ptr)->next; \
}

#define LOR_ITERATOR_NEW_FORWARD_ITERATOR_TYPE(type) \
        LOR_ITERATOR_NEW_FORWARD_ITERATOR_TYPE_HELPER(type, LOR_UNIQUE_COMPILER_STRING)

#define LOR_ITERATOR_RANDOM_ACCESS_ITERATOR(name, type) \
union { \
  lor_iterator_random_access_t methods; \
  type *iter; \
} name = {{NULL, type##_array_next, type##_array_prev, type##_advance}}

#define LOR_ITERATOR_FORWARD_ITERATOR(name, type) \
union { \
  lor_iterator_forward_t methods; \
  type *iter; \
} name = {{NULL, type##_next}};

LOR_ITERATOR_NEW_RANDOM_ACCESS_TYPE(int);

int main() {
  
  LOR_ITERATOR_RANDOM_ACCESS_ITERATOR(my_iterator, int);
  
  int array[ARRAY_SIZE];
  int i;
  for(i = 1; i <= ARRAY_SIZE; i++)
    array[i] = i;

  my_iterator.iter = array;
  while(*my_iterator.iter != ARRAY_SIZE)
    my_iterator.iter++;

  my_iterator.iter = array;
  while(*my_iterator.iter != ARRAY_SIZE)
    my_iterator.methods.iter = my_iterator.methods.next(my_iterator.methods.iter);

  return 0; 
}
