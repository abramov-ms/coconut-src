.intel_syntax noprefix

.section .rodata

format1: .asciz "%d\n"
format2: .asciz "%lu\n"

.section .text

.global my_printf

// rdi: int n
my_printf:
  mov rsi, offset format1
  lea rdi, [rip + offset format2]
  sub rsp, 8
  call printf
  add rsp, 8
  ret
