typedef struct vector_s {
  int a;
} vector;

typedef struct list_s {
  int a;
  int b;
} list;

typedef union container_u {
  vector v;
  list l;
} container;

#include <stdio.h>

void function1 (vector vect_param) {
  printf("vector.a = %d\n", vect_param.a);
}

int main () {
  container c1 = {5};
  function1(c1.v);
}
