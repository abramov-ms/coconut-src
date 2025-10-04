#include <stdio.h>

#include "fib.h"

int main() {
  int n = 6;
  int f = rfib(n);
  printf("rfib(%d) = %d\n", n, f);
  return 0;
}
