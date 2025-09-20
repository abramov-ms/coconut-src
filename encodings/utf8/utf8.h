#include <stdint.h>
#include <stddef.h>

typedef struct {
  char str[5];
} glyph_t;

typedef uint32_t codepoint_t;

glyph_t utf8_encode(codepoint_t);
