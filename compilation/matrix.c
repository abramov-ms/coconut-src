#include "matrix.h"
#include "utf8.h"
#include "terminal.h"

static const char* random_rune() {
  const codepoint_t min_codepoint = 0x250;  // ɐ
  const codepoint_t max_codepoint = 0x2AF;  // ʯ

  codepoint_t codepoint =
      min_codepoint + rand() % (max_codepoint - min_codepoint);

  return render_rune(codepoint);
}

void render_frame(const bool* mask, size_t rows, size_t columns) {
  for (size_t i = 0; i < rows; ++i) {
    for (size_t j = 0; j < columns; ++j) {
      if (mask[i * columns + j]) {
        overwrite_cell(i, j, random_rune());
      }
    }
  }
}
