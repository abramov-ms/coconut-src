#include <stdio.h>
#include <unistd.h>

int main() {
  char buf[8192];
  ssize_t bytes = read(STDIN_FILENO, buf, sizeof(buf) - 1);
  if (bytes < 0) {
    return 1;
  }

  buf[bytes] = '\0';
  printf("%s\n", buf);

  return 0;
}
