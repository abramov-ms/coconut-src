#include <stdint.h>
#include <stdio.h>
#include <string.h>

int main() {
  char bytes[4] = {42, 51};

  uint32_t n;
  memcpy(&n, bytes, sizeof(n));

  printf("%u\n", n);
  printf("%d\n", 42 + 51 * 256);

  return 0;
}
