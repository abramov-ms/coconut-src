#include <stdio.h>

#include "caesar.h"

int main() {
  char hello[] = "ifmmp-!xpsme\"";
  caesar_encrypt(hello, sizeof(hello) - 1, -1);
  printf("%s\n", hello);
  return 0;
}
