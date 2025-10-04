#include <stdio.h>

#include "aplusb.h"

void foo() {
  int src = 1;
  int dst;

  asm("mov %1, %0\n\t"
      "add $1, %0"
      : "=r"(dst)
      : "r"(src));

  printf("%d\n", dst);
}

int main() {
  int a = 16;
  int b = 26;
  printf("%d + %d = %d\n", a, b, aplusb(a, b));
}
