.section .rodata

scanf_format:
  .asciz "%d"

printf_format:
  .asciz "n = %d\n"

.global echo

.section .text

echo:
  sub sp, sp, 16

  adr x0, scanf_format
  add x1, sp, 8
  bl scanf

  adr x0, printf_format
  ldr x1, [sp, 8]
  bl printf

  ret


