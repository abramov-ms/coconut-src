.intel_syntax noprefix

.global rfib

.section .text

// rdi: int n
rfib:
  cmp rdi, 2
  jl out

  dec rdi

  call rfib
  push rax

  dec rdi
  call rfib

  pop r8
  add rax, r8

  inc rdi
  inc rdi

  ret

  out:
    mov rax, 1
    ret
