#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* to_bin(uint32_t n, int len) {
  char* buf = malloc(len + 1);

  for (int i = 0; i < len; ++i) {
    if (n & (1 << (len - i - 1))) {
      buf[i] = '1';
    } else {
      buf[i] = '0';
    }
  }

  buf[len] = '\0';

  return buf;
}

void dump_float(float f) {
  // sign exp mant
  // 1    8   23

  // 101010101
  //
  // 1.01010101
  //   ^^^^^^^^
  //     23
  // ^^^^^^^^^^
  //    24
  //
  // 1.11111111 <- 2^24 - 1

  // 1    11    52
  // 2^53

  // mant 3 bytes
  // exp 1 bytes
  // sign

  uint32_t n;
  memcpy(&n, &f, sizeof(n));

  char* sign = to_bin(n >> 31, 1);
  char* exp = to_bin((n << 1) >> (1 + 23), 8);
  char* mant = to_bin(n & ((1 << 23) - 1), 23);

  // (-1)^s * 2^(exp - 127) * 1.mant

  printf(
      "%.10f\n"
      "---\n"
      "sign = %s\n"
      "exp = %s\n"
      "mant = %s\n\n",
      f, sign, exp, mant);

  free(sign);
  free(exp);
  free(mant);
}

void example_dump() {
  dump_float(42.0);
  dump_float(0.0);
  dump_float(-0.0);
  dump_float(1.0 / 0.0);
  dump_float(-1.0 / 0.0);
  dump_float((2.0 / 0.0) - (1.0 / 0.0));
  dump_float(1.83e-44f);
}

void example_consecutive() {
  union {
    float f;
    uint32_t n;
  } fn;

  fn.f = 16777216;  // 2^24

  for (int i = 0; i < 10; ++i) {
    printf("%.10f\n", fn.f);
    fn.n += 1;
  }
}

int main() {
  example_dump();
  example_consecutive();
  return 0;
}
