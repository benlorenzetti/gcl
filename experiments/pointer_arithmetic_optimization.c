#include <stdio.h>
#include <time.h> // for clock_t clock(void);
#include <stdlib.h> // for malloc(), free(), atoi()

/*  Function Pointer Type Declarations
 *
 *  normal pointer to function
 *  int (*func)(int);
 *
 *  pointer to const function -- not allowed
 *  int (const *func)(int);
 *
 *  const pointer to function. Allowed, most be initialized.              
 *  int (*const func)(int) = some_func;
 *
 *  Bonus: pointer to function returning pointer to const
 *  void const *(*func)(int);
 *
 *  triple bonus: const pointer to function returning pointer to const.
 *  void const *(*const func)(int) = func.i
*/

typedef struct iterator_s {
  void *iter;
  void* (*const next)(void*);
} iterator;

void* int_next(void *ptr) {
  return ptr += sizeof(int);
}

#define static_iterator static iterator

int main (int argc, char**argv) {
  int array_size;
  int *array;
  iterator non_static_iter = {NULL, int_next};
  static_iterator static_iter = {NULL, int_next};
  clock_t start_time;
  clock_t ptr_arithmetic;
  clock_t generic_ptr_arithmetic;
  clock_t f_ptr_pass_by_value;
  clock_t const_f_ptr_pass_by_value;
  clock_t const_f_ptr_pass_by_value_struct_member;
  clock_t const_f_ptr_pass_by_value_static_struct_member;

  // Get size of test array from user
  if(argc != 2) {
    printf("Usage: %s <test array size (a natural number)>\n", argv[0]);
    exit(EXIT_FAILURE);
  }
  array_size = atoi(argv[1]);
  printf("Testing next iteration over %d elements:\n", array_size);

  // Generate an array to transverse
  if(NULL == (array = malloc(array_size * sizeof(int))))
    printf("malloc() failure.\n"), exit(EXIT_FAILURE);
  int i;
  for(i=0; i<array_size; i++)
    array[i] = i % array_size;
  array[array_size-1] = array_size;

  // Baseline test
  start_time = clock();
  int *ptr = array;
  while(*ptr != array_size)
    ptr++;
  ptr_arithmetic = clock() - start_time;

  // Inline Test
  start_time = clock();
  void *generic_ptr = array;
  while(array_size != *((int*)generic_ptr))
    generic_ptr += sizeof *array;
  generic_ptr_arithmetic = clock() - start_time;

  // Constant addition with dereference test
  start_time = clock();
  void* generic_ptr2 = array;
  while(array_size != *((int*)generic_ptr2))
    generic_ptr2 = int_next(generic_ptr2);
  const_f_ptr_pass_by_value = clock() - start_time;

  // Struct Dereference Time
  start_time = clock();
  non_static_iter.iter = array;
  while(array_size != *((int*)non_static_iter.iter))
    non_static_iter.iter = non_static_iter.next(non_static_iter.iter);
  const_f_ptr_pass_by_value_struct_member = clock() - start_time;

  // Static Struct Dereference Time
  start_time = clock();
  static_iter.iter = array;
  while(array_size != *((int*)static_iter.iter))
    static_iter.iter = static_iter.next(static_iter.iter);
  const_f_ptr_pass_by_value_static_struct_member = clock() - start_time;

  // Print Results
  printf("%45s: %ld\n", "Standard pointer arithmetic", (unsigned long)ptr_arithmetic); 
  printf("%45s: %ld\n", "Generic pointer arithmetic", (unsigned long)generic_ptr_arithmetic); 
  printf("%45s: %ld\n", "Constant f() pointer", (unsigned long)const_f_ptr_pass_by_value); 
  printf("%45s: %ld\n", "Const f() pointer Member of Struct", (unsigned long)const_f_ptr_pass_by_value_struct_member); 
  printf("%45s: %ld\n", "Const f() pointer memeber of static struct", (unsigned long)const_f_ptr_pass_by_value_static_struct_member); 


  free(array);
  return EXIT_SUCCESS;
}
