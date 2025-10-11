.global aplusb

.section .text

// w0: int a
// w1: int b
// w0: return value
aplusb:
  add w0, w0, w1
  br x30
