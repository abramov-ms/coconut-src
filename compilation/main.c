#include "fs.h"
#include "mask.h"
#include "terminal.h"
#include "matrix.h"

#include <stdio.h>
#include <error.h>
#include <errno.h>

#include <unistd.h>  // usleep()

#define USECONDS_IN_SECOND 1000000
#define MATRIX_FPS 24

void print_usage(FILE* file, const char* executable) {
  fprintf(file, "usage: %s MASK_FILE\n", executable);
}

int main(int argc, const char* argv[]) {
  if (argc != 2) {
    print_usage(stderr, argv[0]);
    return 1;
  }

  char* str;
  if (read_to_string(argv[1], &str) == -1) {
    error(1, errno, "read_to_string");
  }

  size_t rows;
  size_t columns;
  bool* mask;
  mask_from_utf8(str, &mask, &rows, &columns);

  clear_terminal();
  while (true) {
    render_frame(mask, rows, columns);
    usleep(USECONDS_IN_SECOND / MATRIX_FPS);
  }

  free(str);
  free(mask);

  return 0;
}
