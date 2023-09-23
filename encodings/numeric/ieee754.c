#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

void FormatBin(uint64_t x, size_t len, char buf[]) {
  for (size_t i = 0; i < len; ++i) {
    if (x & (1ULL << i)) {
      buf[i] = '1';
    } else {
      buf[i] = '0';
    }
  }

  buf[len] = '\0';
}

void PrintDoubleRepr(double x) {
  uint64_t bits;
  memcpy(&bits, &x, sizeof(bits));

  uint64_t sign = bits >> 63;
  uint64_t exp = (bits << 1) >> 53;
  uint64_t mant = (bits << 12) >> 12;

  printf("x = %f\n", x);

  char buf[64];
  FormatBin(sign, 1, buf);
  printf("sign = %s\n", buf);
  FormatBin(exp, 11, buf);
  printf("exp = %s\n", buf);
  FormatBin(mant, 52, buf);
  printf("mant = %s\n", buf);

  printf("\n");
}

int main() {
  PrintDoubleRepr(2 * 1.23456);
  PrintDoubleRepr(-1.23456);
  PrintDoubleRepr(1.23 / 0.0);
  PrintDoubleRepr(-1.23 / 0.0);
  PrintDoubleRepr(0.0 / 0.0);
  PrintDoubleRepr(1e-312);
}
