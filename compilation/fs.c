#include "fs.h"

#include <stdio.h>
#include <stdlib.h>

int read_to_string(const char* path, char** str) {
  FILE* file = fopen(path, "r");
  if (file == NULL) {
    return -1;
  }

  size_t size = 0;
  size_t capacity = 128;
  *str = malloc(capacity);

  size_t bytes_read;
  while ((bytes_read = fread(*str + size, 1, capacity - size, file)) > 0) {
    size += bytes_read;

    if (size == capacity) {
      *str = realloc(*str, capacity * 2);
      capacity *= 2;
    }
  }

  if (ferror(file)) {
    free(*str);
    return -1;
  }

  if (size == capacity) {
    *str = realloc(*str, size + 1);
    *str[size] = '\0';
  }

  return 0;
}
