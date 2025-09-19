#include <stdint.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
  char str[4];
} glyph_t;

typedef uint32_t codepoint_t;

static int bit_length(codepoint_t cp) {
  int count = 0;

  while (cp > 0) {
    cp >>= 1;
    ++count;
  }

  return count;
}

static void encode1(glyph_t* glyph, codepoint_t cp) {
  // 0xxxxxxx
  glyph->str[0] = cp;
}

static void encode2(glyph_t* glyph, codepoint_t cp) {
  // 110xxxxx 10xxxxxx
  glyph->str[0] = ((cp >> 6) & 0b11111) | 0b11000000;
  glyph->str[1] = (cp & 0b111111) | 0b10000000;
}

static void encode3(glyph_t* glyph, codepoint_t cp) {
  // 1110xxxx 10xxxxxx 10xxxxxx
  glyph->str[0] = ((cp >> 12) & 0b1111) | 0b11100000;
  glyph->str[1] = ((cp >> 6) & 0b111111) | 0b10000000;
  glyph->str[2] = (cp & 0b111111) | 0b10000000;
}

static void encode4(glyph_t* glyph, codepoint_t cp) {
  // 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
  glyph->str[0] = ((cp >> 18) & 0b111) | 0b11110000;
  glyph->str[1] = ((cp >> 12) & 0b111111) | 0b10000000;
  glyph->str[2] = ((cp >> 6) & 0b111111) | 0b10000000;
  glyph->str[3] = (cp & 0b111111) | 0b10000000;
}

glyph_t utf8_encode(codepoint_t cp) {
  glyph_t glyph;
  memset(&glyph, 0, sizeof(glyph));

  int bits = bit_length(cp);

  if (bits <= 7) {
    encode1(&glyph, cp);
  } else if (bits <= 5 + 6) {
    encode2(&glyph, cp);
  } else if (bits <= 4 + 6 + 6) {
    encode3(&glyph, cp);
  } else if (bits <= 3 + 6 + 6 + 6) {
    encode4(&glyph, cp);
  }

  return glyph;
}

static size_t starter_len(unsigned char first) {
  if ((first >> 3) == 0b11110) {
    return 4;
  } else if ((first >> 4) == 0b1110) {
    return 3;
  } else if ((first >> 5) == 0b110) {
    return 2;
  } else if (first < 128) {
    return 1;
  } else {
    abort();
  }
}

size_t utf8_strlen(const char* str) {
  const char* ch = str;

  size_t length = 0;

  while (*ch != '\0') {
    size_t bytes = starter_len(*ch);
    length += 1;
    ch += bytes;
  }

  return length;
}
