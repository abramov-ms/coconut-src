#include <stdlib.h>

#include <unistd.h>
#include <error.h>
#include <errno.h>

ssize_t read_all(int fd, char buffer[], size_t count) {
  size_t done = 0;

  while (done < count) {
    ssize_t bytes = read(fd, buffer + done, count - done);

    if (bytes < 0) {
      return bytes;
    } else if (bytes == 0) {
      break;
    }

    done += bytes;
  }

  return done;
}

ssize_t write_all(int fd, char buffer[], size_t count) {
  size_t done = 0;

  while (done < count) {
    ssize_t bytes = write(fd, buffer + done, count - done);

    if (bytes < 0) {
      return bytes;
    }

    done += bytes;
  }

  return done;
}

int main() {
  char buffer[128];

  ssize_t bytes = read_all(STDIN_FILENO, buffer, sizeof(buffer));
  if (bytes < 0) {
    error(EXIT_FAILURE, errno, "read_all");
    return 1;
  }

  if (write_all(STDOUT_FILENO, buffer, bytes) < 0) {
    error(EXIT_FAILURE, errno, "write_all");
    return 1;
  }

  return 0;
}
