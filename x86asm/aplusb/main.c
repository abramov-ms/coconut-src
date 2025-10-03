#include <stdio.h>

#include "aplusb.h"

int main() {
  int a = 42;
  int b = 27;
  printf("%d + %d = %d\n", a, b, aplusb(a, b));
}
