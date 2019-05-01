#ifndef _PROCESS_H_
#define _PROCESS_H_

#include <sys/types.h>

#define CHILD_CPU 1
#define PARENT_CPU 0

/* Running one unit time */
#define UNIT_T()				\
{						\
	volatile unsigned long i;		\
	for (i = 0; i < 1000000UL; i++);	\
}
						\
#define exec_unit_time()   { volatile unsigned long i; for(i=0;i<1000000UL;i++); }

typedef struct _Process
{
    char name[32];
    int ready_time;
    int exec_time;
    pid_t pid;
}Process;

/* Assign process to specific core */
int proc_assign_cpu(int pid, int core);

/* Execute the process and return pid */
int proc_exec(Process proc);

/* Set very low priority tp process */
int proc_block(int pid);

/* Set high priority to process */
int proc_wakeup(int pid);

#endif
