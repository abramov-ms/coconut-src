#include <unistd.h>

ssize_t read_all(int fd, char buf[], size_t count) {
  size_t done = 0;
  while (done < count) {
    ssize_t bytes = read(fd, buf, count - done);
    if (bytes < 0) {
      return bytes;
    } else if (bytes == 0) {
      break;
    }

    done += bytes;
  }

  return done;
}

ssize_t write_all(int fd, char buf[], size_t count) {
  size_t done = 0;
  while (done < count) {
    ssize_t bytes = write(fd, buf, count - done);
    if (bytes < 0) {
      return bytes;
    }

    done += bytes;
  }

  return done;
}

int main() {
  char buf[128];

  ssize_t bytes = read_all(STDIN_FILENO, buf, sizeof(buf));
  if (bytes < 0) {
    return 1;
  }

  if (write_all(STDOUT_FILENO, buf, bytes) < 0) {
    return 1;
  }

  return 0;
}
