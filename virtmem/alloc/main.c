#include <stdlib.h>
#include <unistd.h>
#include <malloc.h>

int main() {
  const char hello[] = "hi mom";
  write(STDOUT_FILENO, hello, sizeof(hello));

  const size_t size = 1;
  void* ptr = malloc(size);

  // heap
  // ...............................[obj] ->
  //                                    ^

  pause();

  free(ptr);

  return 0;
}
