#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, const char* argv[]) {
  if (argc < 2) {
    fprintf(stderr, "usage: %s COMMAND [COMMAND...]", argv[0]);
    return EXIT_FAILURE;
  }

  int n_commands = argc - 1;
  const char** commands = argv + 1;

  pid_t last;
  int prev_stdout;
  int pipe_fds[2];
  // pipe
  // -> 1 -> 0 -> parent
  // -> 1 -> 0 -> child

  // stdin -> proc1 -> pipe1 -> proc2 -> pipe2 -> proc3 -> stdout

  for (int i = 0; i < n_commands; ++i) {
    if (i < n_commands - 1) {
      if (pipe(pipe_fds) == -1) {
        err(EXIT_FAILURE, "pipe");
      }
    }

    switch (last = fork()) {
      case -1:
        err(EXIT_FAILURE, "fork");
      case 0:
        if (i > 0) {
          dup2(prev_stdout, STDIN_FILENO);
        }
        if (i < n_commands - 1) {
          // close(pipe_fds[0]);
          dup2(pipe_fds[1], STDOUT_FILENO);
        }
        execlp(commands[i], commands[i], NULL);
        err(EXIT_FAILURE, "exec");
      default:
        if (i > 0) {
          // close(prev_stdout);
        }
        if (i < n_commands - 1) {
          // close(pipe_fds[1]);
          prev_stdout = pipe_fds[0];
        }
    }
  }

  int status;
  waitpid(last, &status, /*options=*/0);
  for (int i = 1; i < n_commands; ++i) {
    wait(NULL);
  }

  if (WIFEXITED(status)) {
    return WEXITSTATUS(status);
  }
  return EXIT_FAILURE;
}
