#include <schedule_fcfs.h>

//sceduling for first come first serve

// TCB_TypeDef *tcb_queue.current_task;
// TCB_TypeDef *sleep_task_fcfs;

uint32_t TASK_ID_FCFS = 1000;
uint32_t exec_start_time_fcfs = 0;
TCB_TypeDef task_fcfs[MAX_TASK];
uint32_t GLOBAL_COUNT_FCFS = 0;

void create_task_fcfs(TCB_TypeDef *tcb, void(*task)(void), uint32_t *stack_start){
	tcb->magic_number = 0xFECABAA0;
    tcb->digital_sinature = 0x00000001;
    tcb->task_id = TASK_ID_FCFS++;
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
	for(int i = 0; i < 5; i++) *(--tcb->psp) = 0x00000000;
	*(--tcb->psp) = (uint32_t)tcb;
	//store R4 - R10
	for(int i = 0; i < 7; i++) *(--tcb->psp) = 0x00000000;
}


void next_task_fcfs(void){
    // first come first serve
    uint32_t time = __getTime();
    tcb_queue.current_task->execution_time += time - tcb_queue.current_task->response_time_t;
    tcb_queue.current_task = pop_task();
    tcb_queue.current_task->response_time_t = time;
    tcb_queue.current_task->waiting_time += time - exec_start_time_fcfs;

    tcb_queue.current_task->status = RUNNING;
    return;
}

void start_exec_fcfs(void){

	if(tcb_queue.size == 0)return;
	tcb_queue.current_task = pop_task(); 


	if(tcb_queue.current_task->magic_number != 0xFECABAA0
	|| tcb_queue.current_task->digital_sinature != 0x00000001){
		kprintf("Invalid task\n");
		return;
	}
    uint32_t cur_time = get_time();
    exec_start_time_fcfs = cur_time;
    tcb_queue.current_task->response_time_t = cur_time;
	tcb_queue.current_task->status = RUNNING;
	start_task(tcb_queue.current_task->psp);
}


//attribute = naked -> active
//attribute = weak -> not active
#ifdef RR
void __attribute__((naked)) PendSV_Handler(void){
	SCB->ICSR |= (1<<27);
	asm volatile(
		"stmdb r0!, {r4-r11}\n"
		"push {lr}\n"
	);
    
	next_task_fcfs();

	asm volatile(
		"mov r0, %0" 
		: 
		:"r"(tcb_queue.current_task->psp)
	);
	asm volatile(
		"ldmia r0!,{r4-r11}\n"
		"msr psp, r0\n"
		"pop {lr}\n"
		"bx lr\n"
	);
}
#endif

// __________________SCHEUDLING TESTER__________________




void task_1_fcfs(void);
void print_all_task(void);
void print_task_timing_data(void);
void scheduling_tester_fcfs(void);
void sleep_state_fcfs(void);


void task_1_fcfs(void){
	uint32_t value;
	uint32_t inc_count=0;
	uint32_t pid = getpid();
	//default loop runs 100000000 times
	// uint32_t loop = 10000000;
	// while(loop--){
	// 	asm("nop");
	// }

	kprintf("________________________Task pid: %d\n\r", pid);
	while(1){
		value = GLOBAL_COUNT_FCFS;
		value++;
		if(value != GLOBAL_COUNT_FCFS+1){ //we check is someother task(s) increase the count
			kprintf("Error %d != %d\n\r",value,GLOBAL_COUNT_FCFS+1); /* It is an SVC call*/
		} else{
			GLOBAL_COUNT_FCFS=value;
			inc_count++;
		}
		if(GLOBAL_COUNT_FCFS >= STOP+100000){
			kprintf("Total increment done by task %d is: %d\n\r",pid,inc_count);
			break;
		}
	}
	task_exit();

}

void sleep_state_fcfs(void){
	print_task_timing_data();
	kprintf("Sleeping\n");
	while(1);
}

void scheduling_tester_fcfs(void){
	scheduling_algo = 1;

	kprintf("\n\n________START SCHEDULING TESTER FOR FCFS________\n");

	init_queue();
	
	for(int i = 0;i < TASK_COUNT;i++){
		create_task_fcfs((TCB_TypeDef *)task_fcfs + i,task_1_fcfs,
        (uint32_t*)TASK_STACK_START - i * TASK_STACK_SIZE);
		push_task((TCB_TypeDef *)task_fcfs + i);
	}
    create_tcb((TCB_TypeDef *)&tcb_queue.sleep, sleep_state_fcfs, 
    (uint32_t *)TASK_STACK_START - TASK_COUNT * TASK_STACK_SIZE);
	start_exec_fcfs();
	
	kprintf("___________END FCFS SCHEDULING TESTER___________\n");
}



void print_all_task(void){
	kprintf("___________________\n");
	for(int i = 0;i < TASK_COUNT;i++){
		kprintf("task id %d\n",((TCB_TypeDef *)task_fcfs + i)->task_id);
		kprintf("task magic number %x\n",((TCB_TypeDef *)task_fcfs + i)->magic_number);
		kprintf("task digital sinature %x\n",((TCB_TypeDef *)task_fcfs + i)->digital_sinature);
		kprintf("task psp %x\n",((TCB_TypeDef *)task_fcfs + i)->psp);
	}
	kprintf("___________________\n");
}

void print_task_timing_data(void) {
    kprintf("_______________________________________________________________\n");
	
    for (int i = 0; i < TASK_COUNT; i++) {
        TCB_TypeDef* task = (TCB_TypeDef*)task_fcfs + i;
        kprintf("Task ID: %d, Execution Time: %d, Waiting Time: %d, Response Time: %d Turn Around Time: %d\n",
                task->task_id, task->execution_time, task->waiting_time, task->response_time_t,task->waiting_time + task->execution_time);
    }
    kprintf("_______________________________________________________________\n");
}
