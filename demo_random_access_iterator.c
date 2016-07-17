#include <stdio.h>  // for printf()
#include <stdlib.h> // for atoi() and exit()
#include <time.h>   // for clock() and clock_t

#define LOR_VECTOR_NAMESPACE vec
#include "lor_vector.h"
#include "lor_iterator.h"

//LOR_ITERATOR_NEW_RANDOM_ACCESS_TYPE(int);

typedef struct lor_iterator_int_s {
  int* iter;
  int* (*const next)(int*);
  int* (*const prev)(struct lor_iterator_int_s*);
  int* (*const advance)(struct lor_iterator_int_s*, unsigned int);
} lor_iterator_int_t;

static int* int_next(int *ptr) {
  return ++ptr;
}

int main(int argc, char** argv) {
  // Get the desired size for the test vector
  if(argc != 2){
    printf("Usage: %s <test vector size (a natural number)>\n", argv[0]);
    exit(EXIT_FAILURE);
  }
  int test_size = atoi(argv[1]);

  // Initializing a Test Vector
  printf("Building a test vector with %d integers\n", test_size);
  vec_t natural_numbers = LOR_VECTOR(int, NULL, NULL);
  int i;
  for(i = 1; i<=test_size; i++)
    vec.push_back(&natural_numbers, i);

  // Iterate through vector using normal pointer arithmetic
  clock_t ptr_time = clock();
  int *ptr = natural_numbers.begin;
  while(*ptr != test_size)
    ptr++;
  ptr_time = clock() - ptr_time;
  printf("Linear search time scanning through %d integers ", test_size);
  printf("using a pointer: %d\n", (int)ptr_time);

  // Iterate through vector using lor_iterators
  clock_t iter_time = clock();
  lor_iterator_int_t x = {NULL, int_next, NULL, NULL};
  x.iter = natural_numbers.begin;
  while(*x.iter != test_size)
    x.iter = x.next(x.iter);
  iter_time = clock() - iter_time;
  printf("Linear search time scanning through %d integers ", test_size);
  printf("using lor iterator: %d\n", (int)iter_time);
}
