  .global mfib
  .text

  .macro push Rn:req
  sub sp, sp, 16
  str \Rn, [sp]
  .endm

  .macro pop Rn:req
  ldr \Rn, [sp]
  add sp, sp, 16
  .endm

mfib:
  cmp x0, 2
  bge .Limpl

  mov x0, 1
  ret

.Limpl:
  push x30
  push x0
  add x0, x0, 1
  lsl x0, x0, 2
  bl malloc

  // call malloc
  // push (rip + 4)
  // jmp malloc
  // ret ~= pop rip

  // call
  // ret

  // add x30, pc, 4
  // b malloc
  // br x30

  pop x1
  mov w2, 1
  str w2, [x0]
  str w2, [x0, 4]

  mov w2, 0
  mov w3, 1
  mov w4, 2
.Lloop:
  ldr w5, [x0, x2, lsl 2]
  ldr w6, [x0, x3, lsl 2]
  add w5, w5, w6
  str w5, [x0, x4, lsl 2]

  add x2, x2, 1
  add x3, x3, 1
  add x4, x4, 1

  cmp x4, x1
  ble .Lloop

.Lend:
  push x5
  bl free

  pop x0
  pop x30
  ret // br x30
