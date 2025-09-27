#include <sys/stat.h>
#include <stdio.h>
#include <err.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
  struct stat stbuf;

  if (lstat(argv[1], &stbuf) == -1) {
    err(EXIT_FAILURE, "stat");
  }

  printf("inode = %lu\n", stbuf.st_ino);

  return 0;
}
