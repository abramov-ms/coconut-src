#include <fcntl.h>
#include <unistd.h>

int main() {
  int fd = open("hello_world.txt", O_RDONLY);
  char buf[64];
  int bytes_read = read(fd, buf, sizeof(buf));
  write(STDOUT_FILENO, buf, bytes_read);
  return 0;
}
