#include <stdio.h>
#include <stdint.h>
#include <string.h>

void print_binary(uint32_t i, int bits) {
  for (int j = 1 << (bits - 1); j > 0; j >>= 1) {
    printf("%d", (i & j) != 0);
  }
  printf("\n");
}

void print_float(float f) {
  uint32_t ui;
  memcpy(&ui, &f, sizeof(ui));

  // 1
  // 8
  // 23

  printf("%.20f\n", f);

  printf("sign = ");
  print_binary(ui >> 31, 1);

  printf("exponent = ");
  print_binary(((ui << 1) >> 1) >> 23, 8);

  printf("significand = ");
  print_binary(ui & ((1 << 23) - 1), 23);
}

int main() {
  print_float(28.34);
  print_float(0.0000000003);
  print_float(1.0 / 0.0);
  print_float(0.0 / 0.0);
  print_float(-42);
  return 0;
}
