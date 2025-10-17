#include <stdlib.h>
#include <unistd.h>
#include <malloc.h>

int main() {
  const size_t size = 1024 * 1024;
  void* ptr = malloc(size);
  printf("ptr = %p\n", ptr);

  pause();

  free(ptr);
  return 0;
}
