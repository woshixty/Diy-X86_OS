#include "dev/time.h"
#include "comm/types.h"
#include "comm/cpu_instr.h"
#include "os_cfg.h"
#include "cpu/irq.h"

static uint32_t sys_tick;

void do_handler_time(void) {
    sys_tick++;
    
    pic_send_eoi(IRQ0_TIMER);
}

static void init_pit(void) {
    uint32_t reload_count = PIT_OSC_FREQ / (1000.0 / OS_TICK_MS);

    outb(PIT_COMMAND_MODE_PORT, PIT_CHANNLE0 | PIT_LOAD_LOHI | PIT_MODE0);
    outb(PIT_CHANNEL0_DATA_PORT, reload_count & 0xFF);   // 加载低8位
    outb(PIT_CHANNEL0_DATA_PORT, (reload_count >> 8) & 0xFF); // 再加载高8位

    irq_install(IRQ0_TIMER, (irq_handler_t)exception_handler_time);
    irq_enable(IRQ0_TIMER);
}

void time_init(void) {
    sys_tick = 0;
    
    init_pit();
}