#include "terminal.h"

#include <stdio.h>

#define ANSI_ESCAPE "\x1b["

void clear_terminal() {
  printf(ANSI_ESCAPE "2J");
}

void overwrite_cell(size_t row, size_t column, const char* str) {
  printf(ANSI_ESCAPE "%lu;%luH%s", row, column, str);
}
