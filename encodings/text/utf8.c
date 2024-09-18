#include "utf8.h"

#include <assert.h>

#define MAX_RUNE_BYTES 6
#define MAX_CODEPOINT 0x7FFFFFFF

#define CODEPOINT_C(x) ((codepoint_t)x)

#define CONTINUATION_BITS 6
#define CONTINUATION_MARKER CODEPOINT_C(0b10000000)
#define CONTINUATION_MASK CODEPOINT_C(0b00111111)

#define BYTE_BITS 8

int codepoint_bytes(codepoint_t codepoint) {
  if (codepoint < (1 << BYTE_BITS)) {
    return 1;
  }

  int bytes = 0;

  while (codepoint > 0) {
    codepoint >>= CONTINUATION_BITS;
    ++bytes;
  }

  return bytes;
}

static uint8_t sequence_marker(int rune_bytes) {
  if (rune_bytes == 1) {
    return 0;
  } else {
    uint8_t leading_ones = (1 << rune_bytes) - 1;
    return leading_ones << (BYTE_BITS - rune_bytes);
  }
}

static uint8_t rune_byte(codepoint_t codepoint, int rune_bytes, int index) {
  if (index == 0) {
    return sequence_marker(rune_bytes) |
           (codepoint >> (CONTINUATION_BITS * (rune_bytes - 1)));
  } else {
    return CONTINUATION_MARKER |
           ((codepoint >> (CONTINUATION_BITS * (rune_bytes - index - 1))) &
            CONTINUATION_MASK);
  }
}

const char* to_rune(codepoint_t codepoint) {
  static char buffer[MAX_RUNE_BYTES + 1];

  assert(codepoint <= MAX_CODEPOINT);

  int bytes = codepoint_bytes(codepoint);
  for (int i = 0; i < bytes; ++i) {
    buffer[i] = (char)rune_byte(codepoint, bytes, i);
  }

  buffer[bytes] = '\0';

  return buffer;
}

static int count_leading_ones(uint8_t byte) {
  int count = 0;

  uint8_t bit = 1 << 7;
  while (bit > 0) {
    if ((byte & bit) == 0) {
      break;
    }

    bit >>= 1;
    ++count;
  }

  return count;
}

int rune_bytes(const char* rune) {
  int leading_ones = count_leading_ones(rune[0]);
  return leading_ones == 0 ? 1 : leading_ones;
}

static uint8_t trim_leading_bits(uint8_t byte, int bits) {
  return (uint8_t)(byte << bits) >> bits;
}

codepoint_t to_codepoint(const char* rune) {
  int bytes = rune_bytes(rune);

  const int marker_bits = bytes == 1 ? 0 : bytes + 1;
  codepoint_t codepoint = trim_leading_bits(rune[0], marker_bits);

  for (int i = 1; i < bytes; ++i) {
    codepoint <<= CONTINUATION_BITS;
    codepoint |= trim_leading_bits(rune[i], BYTE_BITS - CONTINUATION_BITS);
  }

  return codepoint;
}

size_t utf8_strlen(const char* str) {
  size_t len = 0;

  const char* c = str;
  while (*c != '\0') {
    int bytes = rune_bytes(c);
    len += bytes;
    c += bytes;
  }

  return len;
}
