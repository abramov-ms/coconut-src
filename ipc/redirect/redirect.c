#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <err.h>

#include <sys/wait.h>

#include <fcntl.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
  // Expect args:
  // 1) argv[0] = this executable
  // 2) argv[1] = file to read from
  // 3) argv[2] = file to write to
  // 4) argv[3], ..., argv[N] = command to run

  if (argc < 4) {
    fprintf(stderr, "usage: %s IN_FILE OUT_FILE COMMAND", argv[0]);
    return EXIT_FAILURE;
  }

  const char* in_file = argv[1];
  const char* out_file = argv[2];

  int in_fd = open(in_file, O_RDONLY);
  if (in_fd == -1) {
    err(EXIT_FAILURE, "open %s", in_file);
  }

  int out_fd = open(out_file, O_WRONLY);
  if (out_fd == -1) {
    err(EXIT_FAILURE, "open %s", out_file);
  }

  // TODO: Redirect I/O.

  char** commandline = &argv[3];
  execvp(commandline[0], commandline);

  err(EXIT_FAILURE, "exec %s", commandline[0]);
}
