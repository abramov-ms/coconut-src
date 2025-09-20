#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#include "utf8.h"

int count_bits(codepoint_t cp) {
  int count = 0;

  while (cp > 0) {
    cp >>= 1;
    count++;
  }

  return count;
}

void encode1(glyph_t* gl, codepoint_t cp) {
  // 0xxxxxx
  gl->str[0] = (char)cp;
}

void encode2(glyph_t* gl, codepoint_t cp) {
  // 110xxxxx 10xxxxxx
  gl->str[0] = (cp >> 6) | 0b11000000;
  gl->str[1] = (cp & 0b111111) | 0b10000000;
}

void encode3(glyph_t* gl, codepoint_t cp) {
  // 1110xxxx 10xxxxxx 10xxxxxx
  gl->str[0] = (cp >> (6 + 6)) | 0b11100000;
  gl->str[1] = ((cp >> 6) & 0b111111) | 0b10000000;
  gl->str[2] = (cp & 0b111111) | 0b10000000;
}

void encode4(glyph_t* gl, codepoint_t cp) {
  // 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
  gl->str[0] = (cp >> (6 + 6 + 6)) | 0b11110000;
  gl->str[1] = ((cp >> (6 + 6)) & 0b111111) | 0b10000000;
  gl->str[2] = ((cp >> 6) & 0b111111) | 0b10000000;
  gl->str[3] = (cp & 0b111111) | 0b10000000;
}

glyph_t utf8_encode(codepoint_t cp) {
  int bits = count_bits(cp);

  glyph_t gl;
  memset(&gl, '\0', sizeof(gl));

  if (bits <= 7) {
    encode1(&gl, cp);
  } else if (bits <= 5 + 6) {
    encode2(&gl, cp);
  } else if (bits <= 4 + 6 + 6) {
    encode3(&gl, cp);
  } else if (bits <= 3 + 6 + 6 + 6) {
    encode4(&gl, cp);
  } else {
    abort();
  }

  return gl;
}
