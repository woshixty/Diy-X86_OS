#ifndef CPU_INSTR_H
#define CPU_INSTR_H

#include "types.h"

static inline uint8_t inb(uint16_t port) {
    uint8_t rv;
    // __asm__ __volatile__ ("inb %1, %0" : "=a"(rv) : "d"(port));
    __asm__ __volatile__("inb %[p], %[v]" : [v]"=a" (rv) : [p]"d"(port));
    return rv;
}

static inline void outb(uint16_t port, uint8_t data) {
    // __asm__ __volatile__ ("outb %0, %1" : : "a"(data), "Nd"(port));
    __asm__ __volatile__("outb %[v], %[p]" : : [p]"d" (port), [v]"a" (data));
}

static inline void cli(void) {
    __asm__ __volatile__ ("cli");
}

static inline void sti(void) {
    __asm__ __volatile__ ("sti");
}

#endif