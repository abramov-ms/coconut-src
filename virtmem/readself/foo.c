#include <stdio.h>
#include <stdint.h>

int foo(int a, int b) {
  return a + b;
}

int main() {
  uint8_t* bytes = (uint8_t*)&foo;

  for (int i = 0; i < 32; ++i) {
    printf("%02x ", bytes[i]);
  }

  printf("\n");
  return 0;
}
