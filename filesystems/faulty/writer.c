#include <unistd.h>

int main() {
  for (int i = 0; i < 100; ++i) {
    const char hello_world[] = "Hello, World!\n";
    write(STDOUT_FILENO, hello_world, sizeof(hello_world));
  }

  return 0;
}
