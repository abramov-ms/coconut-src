#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <error.h>
#include <errno.h>

int main() {
  int fd = open("lorem_ipsum.txt", O_RDONLY);
  if (fd < 0) {
    error(EXIT_FAILURE, errno, "open");
    return 1;
  }

  if (lseek(fd, 123, SEEK_SET) < 0) {
    error(EXIT_FAILURE, errno, "lseek");
    return 1;
  }

  char buffer[64];
  ssize_t bytes = read(fd, buffer, sizeof(buffer));
  if (bytes < 0) {
    error(EXIT_FAILURE, errno, "read");
    return 1;
  }

  if (write(STDOUT_FILENO, buffer, bytes) < 0) {
    error(EXIT_FAILURE, errno, "write");
    return 1;
  }

  return 0;
}
