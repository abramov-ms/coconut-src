  .global rfib
  .text

rfib:
  cmp x0, 2
  bge .Lrecurse

  mov x0, 1
  ret

.Lrecurse:
  sub sp, sp, 16
  str x30, [sp]

  sub x0, x0, 1
  sub sp, sp, 16
  str x0, [sp]
  bl rfib

  ldr x1, [sp]
  str x0, [sp]
  sub x0, x1, 1
  bl rfib

  ldr x1, [sp]
  add sp, sp, 16
  add x0, x0, x1

  ldr x30, [sp]
  add sp, sp, 16
  ret
