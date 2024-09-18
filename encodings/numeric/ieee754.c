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
  // ???
}

int main() {
  dump_double(2 * 1.23456);
  dump_double(-1.23456);
  dump_double(1.23 / 0.0);
  dump_double(-1.23 / 0.0);
  dump_double(0.0 / 0.0);
  dump_double(1e-312);
}
