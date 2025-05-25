#ifndef BOOT_INFO_H
#define BOOT_INFO_H

#define BOOT_RAM_REGION_MAX 10

#include "types.h"

typedef struct _boot_info_t {
    struct {
        uint32_t start;  // Start address of the RAM region
        uint32_t size;   // Size of the RAM region
    } ram_region_cfg[BOOT_RAM_REGION_MAX];

    int ram_region_count;  // Number of RAM regions
} boot_info_t;

#define SECTOR_SIZE             512
#define SYS_KERNEL_LOAD_ADDR    (1024 * 1024)

#endif