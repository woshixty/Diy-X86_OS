#include "core/memory.h"

static void addr_alloc_init(addr_alloc_t* alloc, uint8_t* bits, uint32_t start, uint32_t size, uint32_t page_size) {
    mutex_init(&alloc->mutex);
    alloc->bits = bits;
    alloc->start = start;
    alloc->size = size;
    alloc->page_size = page_size;

    bitmap_init(&alloc->bitmap, bits, alloc->size / page_size, 0);
}

void memory_init(boot_info_t* boot_info) {
    addr_alloc_t addr_alloc;
}