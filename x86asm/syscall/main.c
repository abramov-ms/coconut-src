#include <unistd.h>
#include <sys/syscall.h>

#include "syscall.h"

int main() {
  char hello[] = "Hello, World!\n";
  my_syscall(SYS_write, STDOUT_FILENO, hello, sizeof(hello) - 1, 0, 0, 0);
}
