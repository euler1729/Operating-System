#include <schedule.h>
#include <sem.h>

volatile TaskQueue_TypeDef tcb_queue;
volatile uint32_t if_lock = 0;
volatile uint8_t scheduling_algo = 0;
TCB_TypeDef tcb_list[MAX_TASK];
uint32_t TASK_ID = 1000, exec_start_time = 0;

//-------------scheduling functions----------------
void schedule_next(void) {
	if (tcb_queue.current_task->status == RUNNING) {
		tcb_queue.current_task->status = READY;
		push_task(tcb_queue.current_task);
	}
	if (tcb_queue.current_task->status == KILLED) {
		uint32_t turn_around_time = __getTime() - tcb_queue.current_task->start_time_t;
		tcb_queue.current_task->waiting_time = turn_around_time - tcb_queue.current_task->execution_time;
	}
	tcb_queue.current_task->execution_time += PER_TASK_TIME;
	tcb_queue.current_task = pop_task();
	tcb_queue.current_task->status = RUNNING;
	//Timing calculation
	if (tcb_queue.current_task->response_time_t == 0) {
		tcb_queue.current_task->response_time_t = __getTime();
	}


	return;
}


void start_exec(void) {
	if (tcb_queue.size == 0)return;
	tcb_queue.current_task = pop_task();
	if (tcb_queue.current_task->magic_number != 0xFECABAA0
		|| tcb_queue.current_task->digital_sinature != 0x00000001) {
		kprintf("Invalid task\n");
		return;
	}
	uint32_t cur_time = get_time();
	tcb_queue.current_task->response_time_t = cur_time;
	exec_start_time = cur_time;
	tcb_queue.current_task->status = RUNNING;
	start_task(tcb_queue.current_task->psp);
}

void create_tcb(TCB_TypeDef* tcb, void(*task)(void), uint32_t* stack_start) {
	tcb->magic_number = 0xFECABAA0;
	tcb->digital_sinature = 0x00000001;
	tcb->task_id = TASK_ID++;
	tcb->status = READY;
	tcb->execution_time = 0;
	tcb->waiting_time = 0;
	tcb->start_time_t = get_time();
	tcb->priority = 1;
	tcb->response_time_t = 0;

	tcb->psp = stack_start;
	*(--tcb->psp) = DUMMY_XPSR; //xPSR
	*(--tcb->psp) = (uint32_t)task; //PC
	*(--tcb->psp) = 0xFFFFFFFD; //LR

	//store R0 - R3, R12
	for (int i = 0; i < 5; i++) *(--tcb->psp) = 0x00000000;
	*(--tcb->psp) = (uint32_t)tcb;
	//store R4 - R10
	for (int i = 0; i < 7; i++) *(--tcb->psp) = 0x00000000;
}

//attribute = naked -> active
//attribute = weak -> not active
#ifndef RR
#define RR
void __attribute__((naked)) PendSV_Handler(void) {
	//Clear all pending interrupts
	SCB->ICSR |= (1 << 27);

	//save current context
	asm volatile(
		"mrs r0, psp\n"
		"stmdb r0!, {r4-r11}\n"
		"push {lr}\n"
		);

	asm volatile("mov %0, r0"
		: "=r" (tcb_queue.current_task->psp)
		:
		);
	//Schedule next task
	if(scheduling_algo == 0)
		schedule_next();
	else if(scheduling_algo == 1)
		next_task_fcfs();

	asm volatile(
		"mov r0, %0"
		:
	: "r"(tcb_queue.current_task->psp)
		);
	asm volatile(
		"ldmia r0!,{r4-r11}\n"
		"msr psp, r0\n"
		"pop {lr}\n"
		"bx lr\n"
		);
}
#endif
//-------------helper functions----------------

uint32_t GLOBAL_COUNT = 0;

void task_with_semaphore(void);
void sleep_state(void);
void scheduling_tester(void);
void print_task_time(void);

void task_with_semaphore(void) {
	uint32_t pid = getpid();
	uint32_t value, inc_count1 = 0;

	wait(); //increment semaphore (critical section)
	kprintf("________________________Task pid: %d\n\r", pid);
	signal(); //increment semaphore (critical section)
	while (1) {
		wait(); //increment semaphore (critical section)
		value = GLOBAL_COUNT;
		value++;
		uint8_t is_valid = (value != GLOBAL_COUNT + 1);
		signal(); //increment semaphore (critical section)
		if (is_valid) {
			wait(); //increment semaphore (critical section)
			kprintf("Error in pid %d with %d != %d\n\r", pid, value, GLOBAL_COUNT + 1);
			signal();
		}
		else {
			wait(); //decrement semaphore (critical section)
			GLOBAL_COUNT = value;
			inc_count1++;
			signal(); //increment semaphore (critical section)
		}
		wait(); //decrement semaphore (critical section
		is_valid = (GLOBAL_COUNT >= STOP);
		signal(); //increment semaphore (critical section)
		if (is_valid) {
			wait(); //decrement semaphore (critical section)
			kprintf("Total increment done by task %d is: %d\n\r", pid, inc_count1);
			signal(); //increment semaphore (critical section)
			break;
		}
	}
	task_exit();
}
void task_no_semaphore(void) {
	uint32_t pid = getpid();
	uint32_t value, inc_count1 = 0;
	kprintf("________________________Task pid: %d\n\r", pid);
	while (1) {
		value = GLOBAL_COUNT;
		value++;
		uint8_t is_valid = (value != GLOBAL_COUNT + 1);
		if (is_valid) {
			kprintf("Error in pid %d with %d != %d\n\r", pid, value, GLOBAL_COUNT + 1);
		}
		else {
			GLOBAL_COUNT = value;
			inc_count1++;
		}
		is_valid = (GLOBAL_COUNT >= STOP);

		if (is_valid) {
			kprintf("Total increment done by task %d is: %d\n\r", pid, inc_count1);
			break;
		}
	}

	task_exit();
}


void sleep_state(void) {
	set_pending(0);
	print_task_time();
	scheduling_tester_fcfs();
	kprintf("Sleeping\n");
	while (1);
}


void scheduling_tester(void) {
	scheduling_algo = 0;
	kprintf("________START SCHEDULING TESTER FOR ROUND ROBIN WITH(OUT) SEMAPHORE________\n");
	init_queue();
	for (int i = 0; i < TASK_COUNT; i++) {
		create_tcb(tcb_list + i, task_with_semaphore, (uint32_t*)(TASK_STACK_START - i * TASK_STACK_SIZE));
		push_task(tcb_list + i);
	}

	create_tcb((TCB_TypeDef*)&tcb_queue.sleep, sleep_state, (uint32_t*)(TASK_STACK_START - TASK_COUNT * TASK_STACK_SIZE));
	set_pending(1);
	start_exec();
	kprintf("________END SCHEDULING TESTER________\n");
}

void print_task_time(void) {
	for (int i = 0;i < TASK_COUNT;i++) {
		TCB_TypeDef* task = (TCB_TypeDef*)tcb_list + i;
		kprintf("Task ID: %d, Execution Time: %d,   Waiting Time: %d,   Response Time: %d   Turn Around Time: %d\n",
			task->task_id, task->execution_time, task->waiting_time, task->response_time_t, task->waiting_time + task->execution_time);
	}

}

