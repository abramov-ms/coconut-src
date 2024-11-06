#include <assert.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <err.h>

#include <unistd.h>

int pipe_fds[2];

void parent() {
  uint8_t byte;

  ssize_t status;
  while ((status = read(pipe_fds[0], &byte, sizeof(byte))) > 0) {
    printf("got ping: %d\n", (int)byte);
  }

  assert(status == 0 && "read() failed?");

  close(pipe_fds[0]);
}

void child() {
  const int pings = 10;

  for (int i = 0; i < pings; ++i) {
    uint8_t byte = i;
    ssize_t status = write(pipe_fds[1], &byte, sizeof(byte));
    assert(status == 1 && "write() failed?");
    usleep(500000);
  }

  close(pipe_fds[1]);
}

int main() {
  int status = pipe(pipe_fds);
  assert(status == 0 && "pipe() failed");

  pid_t pid = fork();
  if (pid == -1) {
    err(EXIT_FAILURE, "fork");
  }

  if (pid == 0) {
    close(pipe_fds[0]);
    child();
  } else {
    close(pipe_fds[1]);
    parent();
  }

  return EXIT_SUCCESS;
}
