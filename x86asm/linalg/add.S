  .intel_syntax noprefix

  .global vadd
  .text

#define FLOAT_BYTES 4
#define YMM_FLOATS 8
#define YMM_BYTES 32

// size_t size = rdi
// const float* lhs = rsi
// const float* rhs = rdx
// float* sum = rcx
vadd:
  push r11
  push r12

  mov r10, rdx
  mov rdx, 0
  mov rax, rdi
  mov r11, YMM_FLOATS
  div r11

  // quotient = rax
  // remainder = rdx
  cmp rax, 0
  je .Ladd_remainder

  mov r8, 0
  mov r11, 0
.Lloop_over_chunks:
  vmovups ymm1, [rsi + r11]
  vmovups ymm2, [r10 + r11]
  vaddps ymm1, ymm1, ymm2
  vmovups [rcx + r11], ymm1

  inc r8
  add r11, YMM_BYTES
  cmp r8, rax
  jl .Lloop_over_chunks

.Ladd_remainder:
  cmp rdx, 0
  je .Lend

  mov r8, 0
  imul rax, YMM_BYTES
.Lloop_over_remainder:
  movss xmm0, [rsi + rax]
  movss xmm1, [r10 + rax]
  addss xmm0, xmm1
  movss [rcx + rax], xmm0

  inc r8
  add rax, FLOAT_BYTES
  cmp r8, rdx
  jl .Lloop_over_remainder

.Lend:
  pop r12
  pop r11

  ret
