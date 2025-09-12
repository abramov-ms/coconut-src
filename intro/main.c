#include <stdio.h>

int invoke_ub(int y);

int main(int argc, char* argv[]) {
  printf("%d\n", invoke_ub(argc));
  return 0;
}
