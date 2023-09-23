#include <stdio.h>
#include <sys/stat.h>

int main() {
  struct stat stbuf;

  stat("lorem_ipsum.txt", &stbuf);
  printf("dev = %lu, inode = %lu\n", stbuf.st_dev, stbuf.st_ino);

  stat("hard_link.txt", &stbuf);
  printf("dev = %lu, inode = %lu\n", stbuf.st_dev, stbuf.st_ino);

  lstat("soft_link.txt", &stbuf);
  printf("dev = %lu, inode = %lu\n", stbuf.st_dev, stbuf.st_ino);

  return 0;
}
