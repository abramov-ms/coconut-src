  .intel_syntax noprefix

  .global echo
  .text

echo:
  sub rsp, 8

  mov rdi, offset scanf_str
  mov rsi, rsp
  call scanf

  mov rdi, offset printf_str
  mov esi, [rsp]
  call printf

  add rsp, 8
  ret
  
  .section .rodata

scanf_str:
  .string "%d" 

printf_str:
  .string "number = %d\n"
