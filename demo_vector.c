#include <stdio.h>

// Define the desired namespace before including lor_vector.h
#define LOR_VECTOR_NAMESPACE vec
#include "lor_vector.h"

/* See city_class.h for how to create a "class" from a struct and proper
   prototypes for "member" functions */
#include "city_class.h"

int main()
{
  /* Initialize a container with the template type (city) and the appropriate
     copy constructor and destructor functions for deep copying. */
  vec_t japanese_cities = LOR_VECTOR(city, city_copy_constructor, godzilla);

  // Some example vector operations
  vec.push_back(&japanese_cities, city_const("Tokyo", 13510000));
  vec.push_back(&japanese_cities, city_const("Kyoto", 1474000));
  vec.insert(&japanese_cities, 1, city_const("Hiroshima", 1174000));

  // Print each element in the vector
  city* iter = (city*) japanese_cities.begin;
  while(iter < (city*) japanese_cities.end)
    printf("%s has population %d\n", iter->name, iter->pop), iter++;
}

