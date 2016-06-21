#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LOR_VECTOR_NAMESPACE vector
#include "lor_vector.h"

typedef struct city_s {
  char* name;
  int population;
} city;

const city* const city_const (const char* name, int pop) {
  static city static_city;
  static char* static_name;
  static_name = realloc(static_name, strlen(name));
  strcpy(static_name, name);
  static_city.name = static_name;
  static_city.population = pop;
  return &static_city;
}

int city_copy_constructor(city* dest, const city* src) {
  if(dest->name = malloc(1 + strlen(src->name)))
    strcpy(dest->name, src->name);
  else
    return -1; // define your own error codes less than zero.
  dest->population = src->population;
  return 0; // success code must be zero
}

void godzilla(city* dest) { // godzilla, aka city destructor
  free(dest->name);
}

int main() {
  vector_t japanese_cities = LOR_VECTOR(city, city_copy_constructor, godzilla);
  vector.push_back(&japanese_cities, city_const("Tokyo", 13510000));
  vector.push_back(&japanese_cities, city_const("Kyoto", 1474000));
  vector.insert(&japanese_cities, 1, city_const("Hiroshima", 1174000));

  // Print city populations from the dynamic array
  int i = 0;
  city* city_ptr;
  while (city_ptr = (city*)vector.at(&japanese_cities, i++))
    printf("%s has population %d\n", city_ptr->name, city_ptr->population);

  vector_t primes = LOR_VECTOR(int,NULL,NULL);
  vector.push_back(&primes,(long) 2);
  vector.push_back(&primes, 3);
  for (i=0; i<vector.size(&primes); i++)
    printf("%d\n", *((int*)vector.at(&primes, i)));
}

