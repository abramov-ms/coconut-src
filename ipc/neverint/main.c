#include <stdlib.h>
#include <signal.h>
#include <err.h>
#include <stdbool.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

volatile sig_atomic_t var;

void handle_sigint(int signum) {
  (void)signum;

  // fetch_add

  var += 1;

  void* ptr = malloc(1024);

  free(ptr);
}

int main() {
  malloc(1024);

  struct sigaction sa = {.sa_handler = &handle_sigint};
  if (sigaction(SIGINT, &sa, NULL) == -1) {
    err(EXIT_FAILURE, "sigaction");
  }

  sa.sa_handler = &handle_sigint;
  if (sigaction(SIGQUIT, &sa, NULL) == -1) {
    err(EXIT_FAILURE, "sigaction");
  }

  while (true) {
    pause();
  }
}
