  .intel_syntax noprefix

  .global rfib
  .text

rfib:
  cmp edi, 2
  jge .Lrecurse

  mov eax, 1
  ret

// exp(int* base, float* exp)

.Lrecurse:
// f<int>()
// f<std::conditional_t<std::is_same_v<float, double>, int, void*>>()
  dec edi
  push rdi
  call rfib

  pop rdi
  dec edi
  push rax
  call rfib
  pop rcx

  add eax, ecx
  ret
