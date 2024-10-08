# Содержание

1. `clang -print-targets`.
1. Armv8, AArch64. RISC vs. CISC.
1. Кросс-компиляция, target triple, запуск в эмуляторе. Arm GNU и linaro
   toolchain.
1. Кодирование инструкций и связанные с этим ограничения, `aarch64-elf-objdump`.
1. Регистры и инструкции Arm в доках.
1. ABI вызова функций.
1. Примеры: `status`, `rfib`, `mfib`.
1. Как дебажить.

# Ссылки

1. [Архитектуры Arm](https://en.wikipedia.org/wiki/ARM_architecture_family)
1. [aarch64-linux-gnu-gcc](https://archlinux.org/packages/extra/x86_64/aarch64-linux-gnu-gcc/)
1. [LLVM target triple](https://clang.llvm.org/docs/CrossCompilation.html)
1. [Arm ARM](https://developer.arm.com/documentation/ddi0487/ja/?lang=en)
1. [AAPCS64](https://github.com/ARM-software/abi-aa/blob/main/aapcs64/aapcs64.rst)
1. [Stack alignment](https://community.arm.com/arm-community-blogs/b/architectures-and-processors-blog/posts/using-the-stack-in-aarch32-and-aarch64)
1. [Implementing `push` and `pop`](https://community.arm.com/arm-community-blogs/b/architectures-and-processors-blog/posts/using-the-stack-in-aarch64-implementing-push-and-pop)
1. [Записки предыдущего лектора](https://github.com/victor-yacovlev/fpmi-caos/blob/master/practice/aarch64/README.md)
