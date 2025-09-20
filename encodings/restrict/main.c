#include "sum_prod.h"

#include <stdio.h>

int main() {
  const size_t len = 5;

  int x[] = {1, 2, 3, 4, 5};
  int y[] = {6, 7, 8, 9, 10};
  int sum[len];
  int prod[len];

  sum_prod(sum, prod, x, y, len);

  printf(
      "sum\n"
      "---\n");
  for (size_t i = 0; i < len; ++i) {
    printf("%d\n", sum[i]);
  }

  printf("\n");

  printf(
      "prod\n"
      "---\n");
  for (size_t i = 0; i < len; ++i) {
    printf("%d\n", prod[i]);
  }

  return 0;
}
