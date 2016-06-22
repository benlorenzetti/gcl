#include <stdlib.h>
#include <string.h>

typedef struct city_s {
  char* name;
  int pop;
} city;

const city* const city_const (const char* name, int population)
{
  static city static_city;
  static char* static_name;
  static_name = realloc(static_name, strlen(name));
  strcpy(static_name, name);
  static_city.name = static_name;
  static_city.pop = population;
  return &static_city;
}

int city_copy_constructor(city* dest, const city* src)
{
  if(dest->name = malloc(1 + strlen(src->name)))
    strcpy(dest->name, src->name);
  else
    return -1;
  dest->pop = src->pop;
  return 0;
}

void godzilla(city* dest)
{ // godzilla, aka city destructor
  free(dest->name);
}


