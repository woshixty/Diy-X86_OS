#include "tools/log.h"
#include "comm/cpu_instr.h"
#include "tools/klib.h"

#include <stdarg.h>

#define COM1_PORT 0x3F8

void log_init(void) {
    outb(COM1_PORT + 1, 0x00);    // Disable all interrupts
    outb(COM1_PORT + 3, 0x80);    // Enable DLAB (set baud rate divisor)
    outb(COM1_PORT + 0, 0x03);    // Set divisor to 3 (lo byte) 38400 baud
    outb(COM1_PORT + 1, 0x00);    //                  (hi byte)
    outb(COM1_PORT + 3, 0x03);    // 8 bits, no parity, one stop bit
    outb(COM1_PORT + 2, 0xC7);    // Enable FIFO, clear them, with 14-byte threshold
    outb(COM1_PORT + 4, 0x0F);
}

void log_printf(const char * fmt, ...) {
    char str_buf[128];
    va_list args;

    kernel_memset(str_buf, '\0', sizeof(str_buf));

    va_start(args, fmt);
    kernel_vsprintf(str_buf, fmt, args);
    va_end(args);

    const char * p = str_buf;    
    while (*p != '\0') {
        while ((inb(COM1_PORT + 5) & (1 << 6)) == 0);
        outb(COM1_PORT, *p++);
    }

    outb(COM1_PORT, '\r');
    outb(COM1_PORT, '\n');
}