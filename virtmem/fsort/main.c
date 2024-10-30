#include <err.h>
#include <assert.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>

int cmp_ascii(const void* lhs, const void* rhs) {
  return *(const char*)lhs - *(const char*)rhs;
}

int main(int argc, const char* argv[]) {
  if (argc != 2) {
    printf("usage: %s FILE", argv[0]);
    return EXIT_FAILURE;
  }

  int fd = open(argv[1], O_RDWR);
  if (fd == -1) {
    err(EXIT_FAILURE, "couldn't open file %s", argv[1]);
  }

  struct stat stbuf = {};
  if (fstat(fd, &stbuf) != 0) {
    err(EXIT_FAILURE, "couldn't stat file %s", argv[1]);
  }

  char* ascii =
      mmap(NULL, stbuf.st_size, PROT_READ, MAP_PRIVATE, fd, /*offset=*/0);

  qsort(ascii, stbuf.st_size, sizeof(char), &cmp_ascii);
  munmap(ascii, stbuf.st_size);

  close(fd);

  return 0;
}
