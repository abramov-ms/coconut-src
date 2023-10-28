#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <signal.h>
#include <unistd.h>
#include <fcntl.h>

void noterm(int signum) {
  (void)signum;
  const char message[] = "haha no\n";
  write(STDOUT_FILENO, message, sizeof(message));
}

int main() {
  struct sigaction act = {.sa_handler = &noterm};
  if (sigaction(SIGINT, &act, /*oact=*/NULL) == -1) {
    err(EXIT_FAILURE, "sigaction");
  }

  while (true) {
    pause();
  }

  return EXIT_SUCCESS;
}
