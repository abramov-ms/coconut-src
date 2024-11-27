#include <stdio.h>
#include <inttypes.h>

int main() {
  printf("0x%" PRIXPTR "\n", (uintptr_t)&main);
  return 0;
}
