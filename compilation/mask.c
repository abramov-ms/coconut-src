#include "utf8.h"

#include <stdbool.h>

static bool is_newline(const char* rune) {
  return *rune == '\n';
}

static bool is_fancy_whitespace(const char* rune) {
  static const char* space = "\xe2\xa0\x80";
  return rune[0] == space[0] && rune[1] == space[1] && rune[2] == space[2];
}

static void update_mask_shape(size_t* curr_columns, size_t* rows,
                              size_t* columns) {
  if (*curr_columns > *columns) {
    *columns = *curr_columns;
  }

  *curr_columns = 0;

  *rows += 1;
}

static void infer_mask_shape(const char* str, size_t* rows, size_t* columns) {
  *rows = 0;
  *columns = 0;

  size_t curr_columns = 0;

  const char* rune = str;
  while (*rune != '\0') {
    if (is_newline(rune)) {
      update_mask_shape(&curr_columns, rows, columns);
    } else {
      ++curr_columns;
    }

    int bytes = rune_bytes(rune);
    rune += bytes;
  }

  update_mask_shape(&curr_columns, rows, columns);
}

void mask_from_utf8(const char* str, bool** matrix, size_t* rows,
                    size_t* columns) {
  infer_mask_shape(str, rows, columns);

  *matrix = malloc((*rows) * (*columns) * sizeof(bool));

  size_t row = 0;
  size_t column = 0;

  const char* rune = str;
  while (*rune != '\0') {
    if (is_newline(rune)) {
      while (column < *columns) {
        (*matrix)[row * (*columns) + column] = false;
        ++column;
      }

      ++row;
      column = 0;
    } else if (is_fancy_whitespace(rune)) {
      (*matrix)[row * (*columns) + column] = false;
      ++column;
    } else {
      (*matrix)[row * (*columns) + column] = true;
      ++column;
    }

    int bytes = rune_bytes(rune);
    rune += bytes;
  }
}
