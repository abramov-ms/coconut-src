.intel_syntax noprefix

.text
.global syscall

// System V x64 ABI: rdi, rsi, rdx, rcx, r8, r9.
// x64 Linux syscall ABI: rdi, rsi, rdx, r10, r8, r9.
my_syscall:
    // Push System V args onto stack in reverse order.
    // The 7th argument is already on stack.
    push r9   // 6
    push r8   // 5
    push rcx  // 4
    push rdx  // 3
    push rsi  // 2
    push rdi  // 1

    // Pop syscall args.
    pop rax  // 1
    pop rdi  // 2
    pop rsi  // 3
    pop rdx  // 4
    pop r10  // 5
    pop r8   // 6
    pop r9   // 7

    // Clobbers rax, rcx, and r11.
    syscall

    // Restore rsp after one extra pop.
    sub rsp, 8

    ret
