1. Как посмотреть, в какой ассемблер компилируется Си. Objdump/godbolt.
1. Регистры x86, Intel 8086. i386, amd64, наборы инструкций. `/proc/cpuinfo`.
   `clang -print-architectures`.
1. Специальные регистры `rip`, `rsp`, `rbp`, `rflags`. Флаг компилятора
   `-fno-omit-frame-pointer`.
1. Референс по инструкциям x86. CISC vs RISC.
1. Calling conventions, callee-saved регистры. Виртуальное адресное
   пространство. Memory layout при вызове функции. Выравнивание стека.
1. Примеры: `rfib`, `mfib`, `sse_sqrt`.
1. SSE vs. FPU
1. SIMD. Примеры: vadd. Как дебажить ассемблерный код. Intel intrinsics.
1. Сисколлы, переключение контекста, кольца защиты.
1. simdjson, конвейер, branch prediction.
