#define LOR_ITERATOR_DEFINE_NEW_RANDOM_ACCESS_TYPE(T_type) \
\
static T_type * T_type##_random_access_advance(T_type **iter_addr, int dist){ \
  *iter_addr += dist; \
  return *iter_addr;    \
}                         \
\
typedef struct lor_iterator_random_access_##T_type##_s { \
  T_type *iter; \
  T_type * (*const advance)(T_type **, int);  \
} lor_iterator_random_access_##T_type; \

#define LOR_ITERATOR_RANDOM_ACCESS(T_type) \
{0, T_type##_random_access_advance}

#include <stdio.h>

LOR_ITERATOR_DEFINE_NEW_RANDOM_ACCESS_TYPE(int);

int main () {
  int array[] = {0, -1, -2, -3, -4, -5, -6};
  lor_iterator_random_access_int it = LOR_ITERATOR_RANDOM_ACCESS(int);
  it.iter = array;
  printf("array[0] = %d, ", *it.iter);
  printf("array[4] = %d, ", *it.advance(&it.iter, 4));
  printf("array[2] = %d\n", *(it.iter -= 2));
}

