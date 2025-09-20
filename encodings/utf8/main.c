#include "utf8.h"

#include <stdio.h>

void utf8_print(codepoint_t cp) {
  glyph_t glyph = utf8_encode(cp);
  printf("%s\n", glyph.str);
}

int main() {
  utf8_print(0x1F604);
  utf8_print(0x069C);
  return 0;
}
