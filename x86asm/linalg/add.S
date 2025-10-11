.intel_syntax noprefix

.global vadd

.section .text

// rdi: size_t count
// rsi: const float* lhs
// rdx: const float* rhs
// rcx: float* sum
vadd:
  // 8 floats per register

  mov r8, 0 
  mov r9, 0

  loop:
    vmovups zmm0, [rsi + r9]
    vmovups zmm1, [rdx + r9]
    vaddps zmm2, zmm0, zmm1
    vmovups [rcx + r9], zmm2

    add r8, 16
    add r9, 64

    cmp r8, rdi
    jl loop

  ret
