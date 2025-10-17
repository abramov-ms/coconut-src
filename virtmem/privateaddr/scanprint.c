#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

int n;

int main() {
  scanf("%d", &n);

  char line[128];
  size_t len;

  for (;;) {
    printf("&n = 0x%lX\n", (uintptr_t)&n);
    printf("n = %d\n", n);

    char* lineptr = line;
    getline(&lineptr, &len, stdin);
  }

  return 0;
}
