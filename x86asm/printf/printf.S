.intel_syntax noprefix

.section .rodata

format: .asciz "%d\n"

.global my_printf

.section .text

// rdi: int n
my_printf:
  mov rsi, rdi
  mov rdi, offset format

  sub rsp, 8
  call printf
  add rsp, 8

  ret
