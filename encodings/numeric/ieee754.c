#include <stdio.h>
#include <stdint.h>
#include <string.h>

void format_binary(uint64_t x, int bits, char buf[]) {
  for (int i = 0; i < bits; ++i) {
    if (x & (1ULL << i)) {
      buf[bits - 1 - i] = '1';
    } else {
      buf[bits - 1 - i] = '0';
    }
  }

  buf[bits] = '\0';
}

void dump_double(double x) {
  uint64_t repr;
  memcpy(&repr, &x, sizeof(x));

  uint64_t sign = repr >> 63;
  uint64_t exponent = (uint64_t)(repr << 1) >> 52;
  uint64_t mantissa = (uint64_t)(repr << 12) >> 12;

  printf("sign = %lu, exp = %lu, mantissa = %lu\n", sign, exponent, mantissa);
}

int main() {
  dump_double(2 * 1.23456);
  dump_double(-1.23456);
  dump_double(1.23 / 0.0);
  dump_double(-1.23 / 0.0);
  dump_double(0.0 / 0.0);
}
