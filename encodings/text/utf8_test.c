#include "utf8.h"

#include <string.h>
#include <stdbool.h>
#include <stdio.h>

bool check_codepoint_to_rune(codepoint_t codepoint, const char* expected_rune) {
  const char* actual_rune = to_rune(codepoint);

  if (strcmp(expected_rune, actual_rune) == 0) {
    return true;
  }

  fprintf(stderr, "test failed: codepoint = %lu, want = '%s', got = '%s'\n",
          codepoint, expected_rune, actual_rune);

  return false;
}

bool check_rune_to_codepoint(const char* rune, codepoint_t expected_codepoint) {
  codepoint_t actual_codepoint = to_codepoint(rune);

  if (expected_codepoint == actual_codepoint) {
    return true;
  }

  fprintf(stderr, "test failed: rune = '%s', want codepoint = %lu, got = %lu\n",
          rune, expected_codepoint, actual_codepoint);

  return false;
}

bool check_mapping(codepoint_t codepoint, const char* rune) {
  bool ok = true;

  ok &= check_codepoint_to_rune(codepoint, rune);
  ok &= check_rune_to_codepoint(rune, codepoint);

  return ok;
}

int main() {
  bool ok = true;

  ok &= check_mapping(0x34, "4");
  ok &= check_mapping(0x50, "P");
  ok &= check_mapping(0x61, "a");
  ok &= check_mapping(0x7C, "|");
  ok &= check_mapping(0x43b, "л");
  ok &= check_mapping(0x419, "Й");
  ok &= check_mapping(0x250, "ɐ");
  ok &= check_mapping(0x264, "ɤ");
  ok &= check_mapping(0x293, "ʓ");
  ok &= check_mapping(0x2AF, "ʯ");
  ok &= check_mapping(0x2230, "∰");
  ok &= check_mapping(0x22DE, "⋞");
  ok &= check_mapping(0x2705, "✅");
  ok &= check_mapping(0x2763, "❣");

  if (!ok) {
    fprintf(stderr, "not quite working\n");
    return 1;
  }

  printf("seems just fine\n");
  return 0;
}
