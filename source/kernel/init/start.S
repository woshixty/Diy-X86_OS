
    .text
    .global _start
    .extern kernel_init
_start:
    push %ebp
    mov %esp, %ebp
    mov $0xa060, %eax
    push %eax

    call kernel_init
    jmp .