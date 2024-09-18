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
  uint64_t bits;
  memcpy(&bits, &x, sizeof(bits));

  uint64_t sign = bits >> 63;
  uint64_t exp = (bits << 1) >> 53;
  uint64_t mantissa = (bits << 12) >> 12;

  printf("x = %f\n", x);

  char buf[64];
  format_binary(sign, 1, buf);
  printf("sign = %s\n", buf);
  format_binary(exp, 11, buf);
  printf("exp = %s\n", buf);
  format_binary(mantissa, 52, buf);
  printf("mantissa = %s\n", buf);

  printf("\n");
}

int main() {
  dump_double(2 * 1.23456);
  dump_double(-1.23456);
  dump_double(1.23 / 0.0);
  dump_double(-1.23 / 0.0);
  dump_double(0.0 / 0.0);
  dump_double(1e-312);
}
