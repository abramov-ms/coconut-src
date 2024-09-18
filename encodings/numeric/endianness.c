#include <stdio.h>
#include <stdint.h>
#include <string.h>

void dump_bytes(uint32_t x) {
  uint8_t buffer[sizeof(x)];
  memcpy(buffer, &x, sizeof(x));

  for (size_t i = 0; i < sizeof(x); ++i) {
    printf("%0X ", buffer[i]);
  }
}

int main() {
  dump_bytes(0xDEADBEEF);
  return 0;
}
