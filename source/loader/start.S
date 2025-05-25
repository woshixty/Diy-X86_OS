	// 16位代码，务必加上
  	.code16
 	.text
	.global _start
	.extern loader_entry
_start:
    jmp loader_entry

	.code32
	.text
	.global protect_mode_entry

protect_mode_entry:
	jmp .