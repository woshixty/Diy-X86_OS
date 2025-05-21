__asm__(".code16gcc");

#include "loader.h"

static void show_msg(const char* msg) {
    char c;
    while ((c = *msg++) != '\0') {
        __asm__ __volatile__ (
            "mov $0xe, %%ah\n\t"  // 设置 BIOS 中断功能号
            "int $0x10"
            :
            : "a"(c)              // 将当前字符加载到 AL
        );
    }
}

void loader_entry(void) {
    show_msg("....loading....\n\r");
    for (; ; ) { }
}