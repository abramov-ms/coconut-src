#include <stdio.h>

#include "caesar.h"

int main() {
  char msg[] = "amogus";
  caesar_encrypt(msg, sizeof(msg) - 1, 1);
  printf("%s\n", msg);
  return 0;
}
