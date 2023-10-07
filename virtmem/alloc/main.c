#include <stdlib.h>
#include <unistd.h>
#include <malloc.h>

int main() {
  const char hello[] = "hi mom";
  write(STDOUT_FILENO, hello, sizeof(hello));

  const size_t size = 256 << 10;
  void* ptr = malloc(size);
  free(ptr);

  return 0;
}
