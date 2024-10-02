# Содержание

1. Как посмотреть, в какой ассемблер компилируется Си. Objdump/godbolt.
1. Регистры x86, Intel 8086. i386, amd64, наборы инструкций. `/proc/cpuinfo`.
   `clang -print-targets`.
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

# Ссылки

1. https://codeforces.com/blog/entry/60598?locale=ru
1. https://godbolt.org/
1. https://ecse324.ece.mcgill.ca/_static/8086-die-blog-post/www.righto.com/2020/06/a-look-at-die-of-8086-processor.html
1. https://en.wikipedia.org/wiki/Intel_8086
1. https://en.wikipedia.org/wiki/I386
1. https://en.wikipedia.org/wiki/X86-64
1. https://en.wikipedia.org/wiki/X86#/media/File:Table_of_x86_Registers_svg.svg
1. https://en.wikipedia.org/wiki/Virtual_address_space#/media/File:Virtual_address_space_and_physical_address_space_relationship.svg
1. https://manybutfinite.com/post/journey-to-the-stack/
1. https://github.com/victor-yacovlev/fpmi-caos/tree/master/practice/x86-64
1. https://www.felixcloutier.com/x86/
1. https://en.wikipedia.org/wiki/Floating-point_unit
1. https://en.wikipedia.org/wiki/Instruction_pipelining
1. https://en.wikipedia.org/wiki/Branch_predictor
1. https://en.wikipedia.org/wiki/Memory_bandwidth
1. https://github.com/simdjson/simdjson
1. https://en.wikipedia.org/wiki/Single_instruction,_multiple_data
1. https://en.wikipedia.org/wiki/Protection_ring
1. https://gitlab.com/Lipovsky/sure/-/blob/master/sure/machine/x86_64/context.S?ref_type=heads
1. https://www.intel.com/content/www/us/en/docs/intrinsics-guide/index.html
1. https://habr.com/ru/articles/540136/
1. https://developers.redhat.com/articles/2023/07/31/frame-pointers-untangling-unwinding
1. https://opensource.com/article/23/3/gdb-debugger-call-frame-active-function-calls
