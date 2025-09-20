#include <stddef.h>

void sum_prod(int* sum, int* prod, const int* restrict x, const int* restrict y,
              size_t len) {
  for (size_t i = 0; i < len; ++i) {
    // Без restrict: дважды читаем из памяти x[i], y[i].
    // ---
    // mov    (%rcx,%rax,4),%edx | %edx = x[i]
    // add    (%rsi,%rax,4),%edx | %edx += y[i]
    // mov    %edx,(%rdi,%rax,4) | sum[i] = %edx
    // mov    (%rsi,%rax,4),%edx | %edx = x[i]
    // imul   (%rcx,%rax,4),%edx | %edx *= y[i]
    // mov    %edx,(%r9,%rax,4)  | prod[i] = %edx

    // С restrict: читаем x[i], y[i] один раз.
    // ---
    // mov    (%r10,%rax,4),%edx | %edx = x[i]
    // mov    (%r11,%rax,4),%ecx | %ecx = y[i]
    // lea    (%rdx,%rcx,1),%esi | %esi = %edx + %ecx
    // imul   %ecx,%edx          | %edx *= %ecx
    // mov    %esi,(%rdi,%rax,4) | sum[i] = %esi
    // mov    %edx,(%r9,%rax,4)  | prod[i] = %edx

    // Без restrict компилятор считает, что запись в sum может изменить
    // значения в массивах x, y. Например, если sum и x -- одно и то же место в
    // памяти.
    sum[i] = x[i] + y[i];

    // Поэтому здесь значения из x, y перечитываются.
    prod[i] = x[i] * y[i];
  }
}
