  .text
  .global echo

echo:
  sub sp, sp, 16
  str x30, [sp, 8]

  adr x0, scanf_str
  mov x1, sp
  bl scanf

  adr x0, printf_str
  ldr x1, [sp]
  bl printf

  ldr x30, [sp, 8]
  add sp, sp, 16
  ret

  .section .rodata

scanf_str:
  .string "%d"

printf_str:
  .string "number = %d\n"
