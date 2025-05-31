#include "cpu/cpu.h"
#include "os_cfg.h"
#include "comm/cpu_instr.h"

static segment_desc_t gdt_table[GDT_TABLE_SIZE];

void segment_desc_set(int selector, uint32_t base, uint32_t limit, uint16_t attr) {
    segment_desc_t* desc = gdt_table + selector / sizeof(segment_desc_t);

    if(limit > 0xFFFFF) {
        attr |= SEG_G;
        limit /= 0x1000;
    }

    desc->limit15_0 = limit & 0xFFFF;
    desc->base15_0 = base & 0xFFFF;
    desc->base23_16 = (base >> 16) & 0xFF;
    desc->attr = attr | (((limit >> 16) & 0xF) << 8);
    desc->base31_24 = (base >> 24) & 0xFF;
}

void init_gdt(void) {
    for (int i = 0; i < GDT_TABLE_SIZE; i++) {
        segment_desc_set(i * sizeof(segment_desc_t), 0, 0, 0);
    }
    
    segment_desc_set(KERNEL_SELECTOR_DS, 0, 0xFFFFFFFF, );
    segment_desc_set(KERNEL_SELECTOR_CS, 0, 0xFFFFFFFF, );

    lgdt((uint32_t)gdt_table, sizeof(gdt_table));
}

void cpu_init(void) {
    init_gdt();
}