#include <fcntl.h>
#include <unistd.h>

int main() {
  int fd = open("lorem_ipsum.txt", O_RDONLY);
  if (fd < 0) {
    return 1;
  }

  if (lseek(fd, 123, SEEK_SET) < 0) {
    return 1;
  }

  char buf[64];
  ssize_t bytes = read(fd, buf, sizeof(buf));
  if (bytes < 0) {
    return 1;
  }

  if (write(STDOUT_FILENO, buf, bytes) < 0) {
    return 1;
  }

  return 0;
}
