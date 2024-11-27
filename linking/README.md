# Содержание

## Статическая и динамическая линковка

1. Пайплайн компиляции Си/C++. Binutils `as`, `ar`, `ld`.
1. Статическая линковка, флаг `-static`.
1. Динамическая линковка, `ldd`. Почему у плюсов больше динамических
   зависимостей, как их отключать. `libstdc++.so`, `libgcc.so`.
1. Динамические зависимости `vDSO` и `ld.so`. Секция `.interp`. Как `ld.so`
   грузит в память динамические библиотеки.

## Примеры релокаций

1. Релокации, `readelf -r`.
1. `R_X86_64_PC32`, адресация относительно `rip`.
1. `R_X86_64_64`, абсолютная адресация.
1. Динамические библиотеки, `R_X86_64_GLOB_DAT`, `R_X86_64_REX_GOTP`.
1. Релокации функций через `PLT`.

## ASLR, position-independent code

1. `-fPIC`, `-fPIE`, ASLR.

# Ссылки

1. https://abramov-ms.github.io/coconut/compilation/compilation.html
1. https://compiler-rt.llvm.org/
1. https://en.wikipedia.org/wiki/Address_space_layout_randomization
