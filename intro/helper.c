#include <stdio.h>
#include <stdlib.h>

void helper(int argc) {
  int* ptr = malloc(sizeof(int) * 1024);
  printf("%d\n", ptr[64]);
  free(ptr);
}
