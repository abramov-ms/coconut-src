  .intel_syntax noprefix

  .global rfib
  .text

rfib:
  cmp edi, 2
  jge .Lrecurse

  mov eax, 1
  ret

.Lrecurse:
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
