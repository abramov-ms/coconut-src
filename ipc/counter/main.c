#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <stdbool.h>
#include <unistd.h>

volatile sig_atomic_t counter = 0;
volatile sig_atomic_t done = false;

void inc(int signum) {
  (void)signum;
  ++counter;
}

void end(int signum) {
  (void)signum;
  done = 1;
}

int main() {
  struct sigaction usr1_act = {.sa_handler = &inc};
  if (sigaction(SIGUSR1, &usr1_act, /*oact=*/NULL) == -1) {
    err(EXIT_FAILURE, "sigaction");
  }
  struct sigaction term_act = {.sa_handler = &end};
  if (sigaction(SIGTERM, &term_act, /*oact=*/NULL) == -1) {
    err(EXIT_FAILURE, "sigaction");
  }

  while (!done) {
    pause();
  }

  printf("counter = %d\n", counter);
  return EXIT_SUCCESS;
}
