#include <stdio.h>

#include "sqrt.h"

int main() {
  double x;
  printf("x = ");
  scanf("%lf", &x);

  printf("sqrt(x) = %lf\n", sse_sqrt(x, 1e-9));

  return 0;
}
