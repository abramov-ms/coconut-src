  .intel_syntax noprefix

  .global sse_sqrt
  .text

sse_sqrt:
  mov eax, 2
  cvtsi2sd xmm10, eax

  pxor xmm3, xmm3
  movsd xmm4, xmm0
.Lbin_search:
  movsd xmm5, xmm3
  addsd xmm5, xmm4
  divsd xmm5, xmm10

  movsd xmm6, xmm5
  mulsd xmm6, xmm6

  comisd xmm0, xmm6
  jb .Lupdate_hi
  movsd xmm3, xmm5
  jmp .Ltry_loop
.Lupdate_hi:
  movsd xmm4, xmm5

.Ltry_loop:
  movsd xmm5, xmm4
  subsd xmm5, xmm3
  comisd xmm5, xmm1
  ja .Lbin_search

  movsd xmm0, xmm3
  ret
