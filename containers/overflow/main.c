#include <stdio.h>
#include <stdlib.h>

int main() {
  int megabytes = 0;
  for (;;) {
    size_t size = 10000000;
    int* ptr = malloc(size * sizeof(int));
    for (size_t i = 0; i < size; i += 1024) {
      ptr[i] = 42;
    }
    megabytes += 40;
    printf("%d mb\n", megabytes);
  }
}
