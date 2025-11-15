#include <unistd.h>
#include <err.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char* argv[]) {
  // argv[0] - current executable
  // argv[1] - child #1
  // argv[2] - child #2
  if (argc != 3) {
    return 1;
  }

  // pipefd[0] - for reading
  // pipefd[1] - for writing
  int pipefd[2];
  if (pipe(pipefd) == -1) {
    err(EXIT_FAILURE, "pipe");
  }

  pid_t pid = fork();
  if (pid == -1) {
    err(EXIT_FAILURE, "fork");
  }

  // stdin -> child #1 -> child #2 -> stdout

  if (pid == 0) {
    // child #1

    close(pipefd[0]);
    dup2(pipefd[1], STDOUT_FILENO);

    execlp(argv[1], argv[1], NULL);
    err(EXIT_FAILURE, "exec");
  }

  wait(NULL);

  pid = fork();
  if (pid == -1) {
    err(EXIT_FAILURE, "fork");
  }

  if (pid == 0) {
    // child #2

    close(pipefd[1]);
    dup2(pipefd[0], STDIN_FILENO);

    execlp(argv[2], argv[2], NULL);
    err(EXIT_FAILURE, "exec");
  }

  close(pipefd[0]);
  close(pipefd[1]);

  wait(NULL);

  return 0;
}
