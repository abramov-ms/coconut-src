#include "utf8.h"

#include <string.h>
#include <stdbool.h>
#include <stdio.h>

bool check_codepoint(codepoint_t codepoint, const char* expected_rune) {
  const char* actual_rune = render_rune(codepoint);

  if (strcmp(expected_rune, actual_rune) == 0) {
    return true;
  }

  fprintf(stderr, "test failed: codepoint = %lu, want = '%s', got = '%s'\n",
          codepoint, expected_rune, actual_rune);

  return false;
}

int main() {
  bool ok = true;

  ok &= check_codepoint(0x34, "4");
  ok &= check_codepoint(0x50, "P");
  ok &= check_codepoint(0x61, "a");
  ok &= check_codepoint(0x7C, "|");
  ok &= check_codepoint(0x43b, "л");
  ok &= check_codepoint(0x419, "Й");
  ok &= check_codepoint(0x250, "ɐ");
  ok &= check_codepoint(0x264, "ɤ");
  ok &= check_codepoint(0x293, "ʓ");
  ok &= check_codepoint(0x2AF, "ʯ");
  ok &= check_codepoint(0x2230, "∰");
  ok &= check_codepoint(0x22DE, "⋞");
  ok &= check_codepoint(0x2705, "✅");
  ok &= check_codepoint(0x2763, "❣");

  if (!ok) {
    fprintf(stderr, "not quite working\n");
    return 1;
  }

  printf("seems just fine\n");
  return 0;
}
