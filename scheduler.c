#define _GNU_SOURCE
#include "process.h"
#include "scheduler.h"
#include <stdlib.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sched.h>

/* Last context switch time for RR scheduling */
static int t_last;

/* Current unit time */
static int ntime;

/* Index of running process. -1 if no process running */
static int running;

/* Number of finish Process */
static int finish_cnt;

/* Sort processes by ready time */
// int cmp(const void *a, const void *b) {
// 	return ((Process *)a)->ready_time - ((Process *)b)->ready_time;
// }
int cmp(const void *a , const void *b)
{
    Process c = *(Process *)a;
    Process d = *(Process*)b;
    if(c.ready_time < d.ready_time)
        return -1;
    else if(c.ready_time == d.ready_time)
        return 0;
    else
        return 1;
}




/* Return index of next process  */
int next_process(Process *proc, int nproc, int policy)
{
	/* Non-preemptive */
	if (running != -1 && (policy == SJF || policy == FIFO))
		return running;

	int ret = -1;

	if (policy == PSJF || policy ==  SJF) {
		for (int i = 0; i < nproc; i++) {
			/* if process not ready or has finished , see next one*/
			if (proc[i].pid == -1 || proc[i].exec_time == 0)
				continue;
			/* if find process which has shorter execution time */
			if (ret == -1 || proc[i].exec_time < proc[ret].exec_time)
				ret = i;
		}
	}

	else if (policy == FIFO) {
		for(int i = 0; i < nproc; i++) {
			if(proc[i].pid == -1 || proc[i].exec_time == 0)
				continue;
			if(ret == -1 || proc[i].ready_time < proc[ret].ready_time)
				ret = i;
		}
        }

	else if (policy == RR) {
		if (running == -1) {
			for (int i = 0; i < nproc; i++) {
				if (proc[i].pid != -1 && proc[i].exec_time > 0){
					ret = i;
					break;
				}
			}
		}
		else if ((ntime - t_last) % 500 == 0)  {
			ret = (running + 1) % nproc;
			while (proc[ret].pid == -1 || proc[ret].exec_time == 0)
				ret = (ret + 1) % nproc;
		}
		else
			ret = running;
	}

	return ret;
}

int scheduling(Process *proc, int nproc, int policy)
{
	/* process sorted by read time */
	qsort(proc, nproc, sizeof(Process), cmp);

	/* Initial pid = -1 imply not ready */
	for (int i = 0; i < nproc; i++)
		proc[i].pid = -1;

	/* Set Parent process to single core in order to prevent from preemption */
	proc_assign_cpu(getpid(), PARENT_CPU);
	
	/* Set Parent process a high priority to scheduler. let it use cpu 
		and then we will send all child processes to cpu for exectuing */
	proc_wakeup(getpid());
	

	/* start to execute child process */
	/* Initial scheduler */
	ntime = 0;
	running = -1; // the process which is running in CPU
	finish_cnt = 0;
	
	while(1) 
	{
		//fprintf(stderr, "Current time: %d\n", ntime);

		/* Check if running process finish */

		/* one process is in CPU but has "finished" */
		if (running != -1 && proc[running].exec_time == 0) 
		{
		
#ifdef DEBUG
			fprintf(stderr, "%s finish at time %d.\n", proc[running].name, ntime);
#endif
			//kill(running, SIGKILL);

			/* wait for child process */
			waitpid(proc[running].pid, NULL, 0); // wait the child process until finish.
			printf("%s %d\n", proc[running].name, proc[running].pid);
			running = -1;
			finish_cnt++;

			/* if All process finish */
			if (finish_cnt == nproc)
				break;
		}

		/* Check if process ready and execute */
		for (int i = 0; i < nproc; i++) 
		{
			if (proc[i].ready_time == ntime) 
			{
				proc[i].pid = proc_exec(proc[i]); //if ready, pid != -1
				proc_block(proc[i].pid);
#ifdef DEBUG
				fprintf(stderr, "%s ready at time %d.\n", proc[i].name, ntime);
#endif
			}

		}

		/* Select next running  process */
		int next = next_process(proc, nproc, policy);
		if (next != -1) 
		{
			/* Context switch */
			if (running != next) 
			{
				proc_wakeup(proc[next].pid);
				proc_block(proc[running].pid);
				running = next;
				t_last = ntime;
			}
		}

		/* Run an unit of time */
		UNIT_T();
		if (running != -1)
			proc[running].exec_time--; //process execution time --
		ntime++; /* current time ++ , go through whole schedule flow at each time. */
	}

	return 0;
}
