#include <stdint.h>

typedef struct {
  char str[4];
} glyph_t;

typedef uint32_t codepoint_t;

glyph_t utf8_encode(codepoint_t);
