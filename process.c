#define _GNU_SOURCE
#include "process.h"
#include <sched.h>
#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/syscall.h>
#include "error.h"

/* assign process to specified CPU core_number */
int assign_CPU(int pid , int core_number)
{
    cpu_set_t set;
    CPU_ZERO(&set);
    CPU_SET(core_number , &set);
    
    if(sched_setaffinity(pid , sizeof(set) , &set) == -1) // if error occurs
    {
        // perror("sched_setaffinity");
        // exit(EXIT_FAILURE);
		ERR_EXIT("sched_setaffinity while assign CPU");
    }
    return 0;

}

int process_execute(Process proc)
{
    struct timespec start, end;
    int current_pid;
    int pid = fork();
    if(pid < 0){
        perror("fork error:");
        return -1;
    }
    if(pid == 0) //child process
	{ 
        current_pid = getpid();
        syscall(345, 1, &start.tv_sec, &start.tv_nsec, &end.tv_sec, &end.tv_nsec, &current_pid);

        for (int i = 0; i < proc.exec_time; i++) {
			exec_unit_time();

/* print out x00/exec_time */
#ifdef DEBUG
		int execution_check_point = 100;
			if (i % execution_check_point == 0)
				printf("%s: %d/%d\n", proc.name, i, proc.exec_time);
#endif

		}
        syscall(345, 0, &start.tv_sec, &start.tv_nsec, &end.tv_sec, &end.tv_nsec, &current_pid);
		exit(0);
    }
	/* Assign child to another core prevent from interupted by parant */
	assign_CPU(pid, CHILD_CPU);
    return pid;
}

int proc_block(int pid)
{
	struct sched_param param;
	
	/* SCHED_IDLE should set priority to 0 */
	param.sched_priority = 0;

	/* set the program as a low priority background process */
	int check = sched_setscheduler(pid, SCHED_IDLE, &param);
	
	if (check < 0) {
		// perror("sched_setscheduler");
		// return -1;
		ERR_EXIT("sched_setscheduler while SCHED_IDLE");
	}

	return check;
}

/* set process{pid} a priority */
int proc_wakeup(int pid)
{
	struct sched_param param;
	
	/* SCHED_OTHER should set priority to 0 */
	param.sched_priority = 0;

	/* Let the process can use CPU as the next one, because it has highest priority now */
	int check = sched_setscheduler(pid, SCHED_OTHER, &param);
	
	if (check < 0) {
		// perror("sched_setscheduler");
		// return -1;
		ERR_EXIT("sched_setscheduler while SCHED_OTHER");
	}

	return check;
}
