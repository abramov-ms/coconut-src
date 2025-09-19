#include "utf8.h"

#include <stdio.h>

void utf8_print(codepoint_t cp) {
  glyph_t glyph = utf8_encode(cp);
  printf("%s\n", glyph.str);
}

int main() {
  utf8_print(0x1F643);
  utf8_print(0x1F37E);
  utf8_print(0x0B9C);
  return 0;
}
