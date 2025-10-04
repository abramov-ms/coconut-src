.intel_syntax noprefix

.global aplusb

.section .text

#define amogus rax

// rdi: int a
// rsi: int b
// rax: return value
aplusb:
  mov amogus, rdi // rax <- rdi
  add amogus, rsi // rax += rsi
  ret
  
