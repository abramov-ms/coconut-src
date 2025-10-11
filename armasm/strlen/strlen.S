.global my_strlen

.section .text

// x0: const char* str
// x0: return value
my_strlen:
  // ldr / str
  // ldr x1, [base, shift, scale]

  mov x2, 0

  loop:
    ldrb w1, [x0]
    add x0, x0, 1
    add x2, x2, 1

    cmp x1, 0
    bgt loop

    add x0, x0, 1

  sub x2, x2, 1
  mov x0, x2

  ret



