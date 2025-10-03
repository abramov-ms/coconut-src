.intel_syntax noprefix

.section .text

.globl aplusb

// edi = a
// esi = b
// eax = result
aplusb:
  mov rax, rdi
  add eax, esi
  ret
