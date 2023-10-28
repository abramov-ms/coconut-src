#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <signal.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, const char* argv[]) {
  if (argc != 2) {
    fprintf(stderr, "usage: %s PROGNAME", argv[0]);
    return EXIT_FAILURE;
  }

  struct sigaction act = {.sa_handler = SIG_IGN};
  if (sigaction(SIGHUP, &act, /*oact=*/NULL) == -1) {
    err(EXIT_FAILURE, "sigaction");
  }

  const char* prog = argv[1];
  execlp(prog, prog);
  return EXIT_FAILURE;
}
