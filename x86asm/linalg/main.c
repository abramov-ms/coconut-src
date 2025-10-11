#include <stdio.h>

#include "add.h"

int main() {
  float v1[] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0,
                1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0};
  float v2[] = {0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8,
                0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8};
  size_t count = sizeof(v1) / sizeof(v1[0]);

  float sum[count];
  vadd(count, v1, v2, sum);

  for (size_t i = 0; i < count; ++i) {
    printf("%f ", sum[i]);
  }

  printf("\n");
  return 0;
}
