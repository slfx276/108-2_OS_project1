#define _GNU_SOURCE
#include "process.h"
#include "scheduler.h"
#include <stdlib.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sched.h>
#include "error.h"

/* Last context switch time for RR scheduling */
static int RR_last_time;

/* Initial scheduler */
/* Current unit time */
static int current_time = 0;

/* Index of running process. -1 if no process running */
static int running = -1; // the process which is running in CPU

/* Number of finish Process */
static int finish_cnt = 0;

/* Sort processes by ready time */
// int cmp(const void *a, const void *b) {
// 	return ((Process *)a)->ready_time - ((Process *)b)->ready_time;
// }

/* Return index of next process  */
int next_process(Process *proc, int process_num, int policy)
{
	/* Non-preemptive */
	if (running != -1 && (policy == SJF || policy == FIFO))
		return running;

	int result = -1;

	if (policy == PSJF || policy ==  SJF) {
		for (int i = 0; i < process_num; i++) {
			/* if process not ready or has finished , see next one*/
			if (proc[i].pid == -1 || proc[i].exec_time == 0)
				continue;
			/* if find process which has shorter execution time */
			if (result == -1 || proc[i].exec_time < proc[result].exec_time)
				result = i;
		}
	}

	else if (policy == FIFO) {
		for(int i = 0; i < process_num; i++) {
			if(proc[i].pid == -1 || proc[i].exec_time == 0)
				continue;
			if(result == -1 || proc[i].ready_time < proc[result].ready_time)
				result = i;
		}
        }

	else if (policy == RR) {
		if (running == -1) {
			for (int i = 0; i < process_num; i++) {
				if (proc[i].pid != -1 && proc[i].exec_time > 0){
					result = i;
					break;
				}
			}
		}
		else if ((current_time - RR_last_time) % 500 == 0)  {
			result = (running + 1) % process_num;
			while (proc[result].pid == -1 || proc[result].exec_time == 0)
				result = (result + 1) % process_num;
		}
		else
			result = running;
	}

	return result;
}

int scheduling(Process *proc, int process_num, int policy)
{
	/* process sorted by read time */
	// qsort(proc, process_num, sizeof(Process), cmp);

	/* Initial pid = -1 imply not ready */
	for (int i = 0; i < process_num; i++)
		proc[i].pid = -1;
	/* Set Parent process to single core in order to prevent from preemption */
	proc_assign_cpu(getpid(), PARENT_CPU);
	
	/* Set Parent process a high priority to scheduler. let it use cpu 
		and then we will send all child processes to cpu for exectuing */
	proc_wakeup(getpid());
	

	/* start to execute child process */

	
	while(1) 
	{
		//fprintf(stderr, "Current time: %d\n", current_time);

		/* Check if running process finish */

		/* one process is in CPU but has "finished" */
		if (running != -1 && proc[running].exec_time == 0) 
		{
		
#ifdef DEBUG
			fprintf(stderr, "%s finish at time %d.\n", proc[running].name, current_time);
#endif
			/* wait for child process */
			waitpid(proc[running].pid, NULL, 0); // wait the child process until finish.
			printf("%s %d\n", proc[running].name, proc[running].pid);
			running = -1;
			finish_cnt += 1;

			/* if All process finish */
			if (finish_cnt == process_num)
				break;
		}

		/* Check if process ready and execute */
		for (int i = 0; i < process_num; i++) 
		{
			if (proc[i].ready_time == current_time) 
			{
				proc[i].pid = proc_exec(proc[i]); //if ready, pid != -1
				proc_block(proc[i].pid);
#ifdef DEBUG
				fprintf(stderr, "%s ready at time %d.\n", proc[i].name, current_time);
#endif
			}

		}

		/* Select next running  process */
		int next_proc = next_process(proc, process_num, policy);
		if (next_proc != -1) 
		{
			/* Context switch */
			if (running != next_proc) 
			{
				proc_wakeup(proc[next_proc].pid);
				proc_block(proc[running].pid);
				running = next_proc;
				RR_last_time = current_time;
			}
		}

		/* Run an unit of time */
		exec_unit_time();
		if (running != -1)
			proc[running].exec_time -= 1; //process execution time --
		current_time += 1; /* current time ++ , go through whole schedule flow at each time. */
	}

	return 0;
}
