#include "comm/boot_info.h"

int test (int a, int b) {
    return a + b;
}

/**
 * 内核入口
 */
void kernel_init (boot_info_t * boot_info) {
    int a = 1, b = 2;
    test(a , b);

    for (;;) {}
}