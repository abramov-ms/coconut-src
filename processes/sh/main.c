#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/wait.h>

void parse_args(char* cmd, char* argv[]) {
  const char* delimiter = " \t\r\n";
  argv[0] = strtok(cmd, delimiter);

  size_t idx = 1;
  char* arg;
  while ((arg = strtok(NULL, delimiter)) != NULL) {
    argv[idx] = arg;
    ++idx;
  }

  argv[idx] = NULL;
}

int main() {
  char* cmdbuf = NULL;
  size_t bufsize;
  while (true) {
    printf("sh %% ");
    if (getline(&cmdbuf, &bufsize, stdin) == EOF) {
      break;
    }

    if (cmdbuf[0] == '\0') {
      continue;
    }
    if (strcmp(cmdbuf, "exit\n") == 0) {
      break;
    }

    char* argv[1024];
    parse_args(cmdbuf, argv);

    pid_t pid = fork();
    if (pid < 0) {
      err(EXIT_FAILURE, "fork failed");
    }
    if (pid == 0) {
      execvp(argv[0], argv);
      err(EXIT_FAILURE, "exec failed");
    }

    wait(NULL);
  }

  free(cmdbuf);
  return 0;
}
