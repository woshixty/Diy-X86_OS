#include "os_cfg.h"

 	.text
	.extern kernel_init
 	.global _start
    .extern init_main
_start:
    # 第一种方法
    ; # push %ebp
    ; # mov %esp, %ebp
    ; # mov 0x8(%ebp), %eax
    ; # push %eax

    # 第二种方法
    ; # mov 4(%esp), %eax
    ; # push %eax

    # 第三种方法
    push 4(%esp)

    ; # kernel_init(boot_info)
    call kernel_init

    jmp $KERNEL_SELECTOR_CS, $gdt_reload
gdt_reload:
    mov $KERNEL_SELECTOR_DS, %ax
	mov %ax, %ds
    mov %ax, %ss
    mov %ax, %es
    mov %ax, %fs
    mov %ax, %gs

    mov $(stack + KERNEL_STACK_SIZE), %esp
	jmp init_main

    .bss
.comm stack, KERNEL_STACK_SIZE

.macro exception_handler name num with_err_code 
    .text
    .extern do_handler_\name
    .global exception_handler_\name
exception_handler_\name:
    .if \with_err_code == 0
        push $0
    .endif
    push $\num
    pusha
    push %ds
    push %es
    push %fs
    push %gs

    push %esp
    call do_handler_\name
    add $(1*4), %esp

    pop %gs
    pop %fs
    pop %es
    pop %ds
    popa

    add $(2*4), %esp
    iret
.endm

exception_handler unknown, -1, 0
exception_handler divider, 0, 0
exception_handler Debug, 1, 0
exception_handler NMI, 2, 0
exception_handler breakpoint, 3, 0
exception_handler overflow, 4, 0
exception_handler bound_range, 5, 0
exception_handler invalid_opcode, 6, 0
exception_handler device_unavailable, 7, 0
exception_handler double_fault, 8, 1
exception_handler invalid_tss, 10, 1
exception_handler segment_not_present, 11, 1
exception_handler stack_segment_fault, 12, 1
exception_handler general_protection, 13, 1
exception_handler page_fault, 14, 1
exception_handler fpu_error, 16, 0
exception_handler alignment_check, 17, 1
exception_handler machine_check, 18, 0
exception_handler smd_exception, 19, 0
exception_handler virtual_exception, 20, 0

exception_handler time, 0x20, 0