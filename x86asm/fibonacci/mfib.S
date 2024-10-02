  .intel_syntax noprefix

  .global mfib
  .text

mfib:
  cmp edi, 2
  jge .Limpl
  mov eax, 1
  ret

.Limpl:
  push rdi
  add edi, 1
  shl edi, 2
  call malloc

  pop rdi
  mov dword ptr [rax], 1
  mov dword ptr [rax + 1*4], 1

  mov ebx, 0
  mov ecx, 1
  mov edx, 2
.Lloop:
  mov r8d, [rax + rbx*4]
  mov r9d, [rax + rcx*4]
  add r8d, r9d
  mov [rax + rdx*4], r8d

  inc ebx
  inc ecx
  inc edx

  cmp edx, edi
  jle .Lloop

.Lend:
  push r8
  mov rdi, rax
  call free

  pop rax
  ret
