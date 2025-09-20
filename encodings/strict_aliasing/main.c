#include <stdio.h>
#include <stdint.h>

int foo(int* n, float* f) {
  *n = 1;
  *f = 0.0f;
  return *n;
}

int main() {
  int n = 42;
  printf("%d\n", foo(&n, (float*)&n));
  return 0;
}
