#include <unistd.h>
#include <stdio.h>

int main() {
  int pipefd[2];
  pipe(pipefd);

  char msg[] = "hello";

  write(pipefd[1], msg, sizeof(msg) - 1);

  char buf[128];

  int bytes = read(pipefd[0], buf, sizeof(buf));

  buf[bytes] = '\0';
  printf("buf: %s\n", buf);

  return 0;
}
