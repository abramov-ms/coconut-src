#include <stdlib.h>

int fn();

int main() {
  int* i = malloc(sizeof(int));
  free(i);

  return fn();
}
