#include <err.h>
#include <assert.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>

int cmp_ascii(const void* lhs, const void* rhs) {
  return *(char*)lhs - *(char*)rhs;
}

int main(int argc, const char* argv[]) {
  // argv[1]: filename

  int fd = open(argv[1], O_RDWR);
  if (fd == -1) {
    err(EXIT_FAILURE, "open");
  }

  struct stat stbuf;
  if (fstat(fd, &stbuf) == -1) {
    err(EXIT_FAILURE, "stat");
  }

  void* ptr =
      mmap(NULL, stbuf.st_size, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0);
  if (ptr == MAP_FAILED) {
    err(EXIT_FAILURE, "mmap");
  }

  qsort(ptr, stbuf.st_size, 1, &cmp_ascii);

  ((char*)ptr)[stbuf.st_size] = '\0';
  printf("in-memory copy: %s\n", (char*)ptr);

  printf("stdin addr: %p\n", &stdin);

  pause();

  munmap(ptr, stbuf.st_size);
  close(fd);

  return 0;
}
