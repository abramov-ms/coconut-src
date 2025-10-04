.intel_syntax noprefix

.global caesar_encrypt

.section .text

// rdi: char* str
// rsi: size_t len
// edx: int shift
caesar_encrypt:
  xor rcx, rcx

  loop:
    xor r8b, r8b

    // [base + scale*index + offset]
    mov r8b, [rcx + rdi]
    add r8d, edx
    mov [rcx + rdi], r8b
    
    inc rcx
    cmp rcx, rsi
    jl loop

  ret
