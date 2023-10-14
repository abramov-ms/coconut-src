#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

int main() {
  while (true) {
    pid_t pid = fork();
    if (pid == -1) {
      printf("fork failed: %s\n", strerror(errno));
    } else if (pid != 0) {
      printf("child: %d\n", pid);
    }
  }
}
