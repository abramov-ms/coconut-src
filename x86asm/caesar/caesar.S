.intel_syntax noprefix

.section .text

.global caesar_encrypt

// rdi: char* str
// rsi: size_t len
// rdx: int shift
caesar_encrypt:
  mov rcx, 0

  .loop:
    mov r8b, byte ptr [rdi+rcx*1]
    add r8d, edx
    mov byte ptr [rdi+rcx*1], r8b
    add rcx, 1
    cmp rcx, rsi
    jl .loop

  ret

