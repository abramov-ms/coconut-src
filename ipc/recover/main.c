#define _GNU_SOURCE
#include <inttypes.h>
#include <signal.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <ucontext.h>
#include <unistd.h>

bool peek_byte(uintptr_t addr, uint8_t* out_byte) {
  *out_byte = *(uint8_t*)addr;
  return true;
}

bool recover() {
  return false;
}

void handle_segv(int signum, siginfo_t* info, void* ctx) {
  (void)signum;
  (void)info;
  ucontext_t* uctx = ctx;
  uctx->uc_mcontext.gregs[REG_RIP] = (uintptr_t)&recover;
}

int x = 61;

int main() {
  struct sigaction act = {.sa_flags = SA_SIGINFO, .sa_sigaction = &handle_segv};
  sigaction(SIGSEGV, &act, /*oact=*/NULL);

  uint8_t bytes[UINT8_MAX];  // 0, 1, ..., 255
  for (size_t i = 0; i < UINT8_MAX; ++i) {
    bytes[i] = i;
  }
  printf("stack bytes @ [0x%" PRIxPTR ", 0x%" PRIxPTR ")\n", (uintptr_t)bytes,
         (uintptr_t)(bytes + sizeof(bytes)));
  printf("global int @ 0x%" PRIxPTR "\n", (uintptr_t)&x);
  printf("main() @ 0x%" PRIxPTR "\n", (uintptr_t)&main);

  while (true) {
    printf("peek > ");

    uintptr_t addr;
    scanf("%" SCNxPTR, &addr);

    uint8_t byte;
    if (peek_byte(addr, &byte)) {
      printf("<< %" PRIu8 "\n", byte);
    } else {
      printf("<< SEGV\n");
    }
  }
}
