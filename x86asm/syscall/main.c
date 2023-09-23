#include <unistd.h>
#include <sys/syscall.h>

#include "syscall.h"

int main() {
  char hello[] = "Hello, World!";
  my_syscall(SYS_write, hello, sizeof(hello), 0, 0, 0, 0);
}
