	#include "boot.h"

  	// 16位代码，务必加上
  	.code16
 	.text
	.global _start
_start:
	mov $0, %ax
	mov %ax, %ds
	mov %ax, %ss
	mov %ax, %es
	mov %ax, %fs
	mov %ax, %gs

	mov $_start, %esp

	mov $0xe, %ah
	mov $'L', %al
	int $0x10

read_loader:
    mov $0x8000, %bx       // 加载到 0x8000
    mov $0x2, %ah          // BIOS 13h 功能号：读取扇区
    mov $0x2, %cx          // 扇区号 2
    mov $64, %al           // 每次读取 64 个扇区
    mov $0x0080, %dx       // 第一个硬盘
    int $0x13              // 调用 BIOS 中断
	jc read_loader

    jmp .                  // 成功后停止
	
	// 引导结束段
	.section boot_end, "ax"
boot_sig: .byte 0x55, 0xaa
