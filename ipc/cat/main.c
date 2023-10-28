#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

void write_all(int fd, const char buffer[], size_t count) {
  size_t done = 0;
  while (done < count) {
    ssize_t bytes;
    if ((bytes = write(fd, buffer + done, count - done)) == -1) {
      err(EXIT_FAILURE, "write");
    }
    done += bytes;
  }
}

int main(int argc, const char* argv[]) {
  if (argc > 2) {
    fprintf(stderr, "usage: %s [FILE]", argv[0]);
    return EXIT_FAILURE;
  }

  if (argc == 2) {
    int fd;
    const char* file = argv[1];
    if ((fd = open(file, O_RDONLY)) == -1) {
      err(EXIT_FAILURE, "open");
    }

    close(STDIN_FILENO);
    dup(fd);
  }

  ssize_t bytes;
  char buffer[4096];
  while ((bytes = read(STDIN_FILENO, buffer, sizeof(buffer))) > 0) {
    write_all(STDOUT_FILENO, buffer, bytes);
  }

  return EXIT_SUCCESS;
}
