#ifndef _PROCESS_H_
#define _PROCESS_H_
#define CHILD_CPU 1
#define PARENT_CPU 0

#include <sys/types.h>


/* Running one unit time */
#define exec_unit_time()   { volatile unsigned long i; for(i=0;i<1000000UL;i++); }

typedef struct _Process
{
    char name[32];
    int ready_time;
    int exec_time;
    pid_t pid;
    int start_time;
    int finish_time;
    int Have_used_CPU;

}Process;

/* Assign process to specific core */
int assign_CPU(int pid , int core_number);

/* Execute the process and return pid , use system call printk() here. */
int process_execute(Process proc);

/* Set very low priority tp process */
int proc_block(int pid);

/* Set high priority to process */
int proc_wakeup(int pid);

#endif
