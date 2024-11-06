#include <assert.h>
#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, const char* argv[]) {
  if (argc != 3) {
    return 1;
  }
  const char* exe1 = argv[1];
  const char* exe2 = argv[2];

  int pipe_fds[2];
  pipe(pipe_fds);

  if (fork() == 0) {
    close(pipe_fds[0]);
    dup2(pipe_fds[1], STDOUT_FILENO);
    execlp(exe1, exe1, NULL);
  }

  if (fork() == 0) {
    close(pipe_fds[1]);
    dup2(pipe_fds[0], STDIN_FILENO);
    execlp(exe2, exe2, NULL);
  }
  close(pipe_fds[0]);
  close(pipe_fds[1]);

  wait(NULL);
  wait(NULL);

  return 0;
}
