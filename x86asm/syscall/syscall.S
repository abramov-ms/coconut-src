.intel_syntax noprefix

.section .text

.global my_syscall

// rdi: int syscall_no
// rsi: int arg1
// rdx: void* arg2
// rcx: size_t arg3
// r8: int arg4
// r9: int arg5
// <stack>: int arg6
my_syscall:
  mov rax, rdi

  push r9
  push r8
  push rcx
  push rdx
  push rsi

  pop rdi
  pop rsi
  pop rdx
  pop r10
  pop r8
  pop r9

  syscall

  sub rsp, 8

  ret
