#include <stdio.h>

#include "fib.h"

int main() {
  int n;
  printf("n = ");
  scanf("%d", &n);

  printf("rfib(%d) = %d\n", n, rfib(n));
  printf("mfib(%d) = %d\n", n, mfib(n));

  return 0;
}
