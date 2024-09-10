  .intel_syntax noprefix

  .text
  .globl inc
inc:
  movabs rdi, OFFSET counter
  inc DWORD PTR [rdi]
