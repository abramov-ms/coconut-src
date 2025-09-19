#include <stdio.h>
#include <stdint.h>
#include <string.h>

int main() {
  uint8_t bytes[4] = {15, 28};

  // 28 * 256 + 15 = 7183
  int x;
  memcpy(&x, bytes, sizeof(x));

  printf("%d\n", x);

  return 0;
}
