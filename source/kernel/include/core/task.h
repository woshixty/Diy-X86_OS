#ifndef TASK_H
#define TASK_H

#include "comm/types.h"
#include "cpu/cpu.h"
#include "tools/list.h"

#define TASK_NAME_SIZE 32
#define TASK_TIME_SLICE_DEFAULT 10

/**
 * @brief 任务控制块结构
 */
typedef struct _task_t {
	//uint32_t * stack;
	enum {
		TASK_CREATED,
		TASK_RUNNING,
		TASK_SLEEP,
		TASK_READY,
		TASK_WAITING,
	}state;

	int sleep_ticks;
	int time_ticks;
	int slice_ticks;

	char name[TASK_NAME_SIZE];

	list_node_t run_node;
	list_node_t wait_node;
	list_node_t all_node;

	tss_t tss;				// 任务的TSS段
	uint16_t tss_sel;		// tss选择子
}task_t;

int task_init (task_t *task, const char* name, uint32_t entry, uint32_t esp);
void task_switch_from_to (task_t * from, task_t * to);
void task_time_tick(void);

typedef struct _task_manager_t
{
	task_t* curr_task;

	list_t ready_list;
	list_t task_list;
	list_t sleep_list;

	task_t first_task;
	task_t idle_task;
} task_manager_t;

void task_manager_init (void);
void task_first_init (void);
task_t* task_first_task (void);
void task_set_ready (task_t* task);
void task_set_block (task_t* task);

task_t* task_next_run (void);
task_t* task_current (void);
int sys_sched_yield (void);
void task_dispatch (void);

void task_set_sleep (task_t* task, uint32_t ticks);
void task_set_wakeup (task_t* task);

void sys_sleep (uint32_t ms);

#endif