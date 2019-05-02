#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sched.h>
#include <errno.h>
#include <unistd.h>
#include "process.h"
#include "scheduler.h"
#include "error.h"


// /* define comparison for quicksort*/
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

int main(void)
{
	char _policy[5];
	int policy = -1;
	int process_num,i;
	Process *proc;

	scanf("%s", _policy);
	scanf("%d", &process_num);
	
	/* malloc Process array */
	proc = (Process *)malloc(process_num * sizeof(Process));

	for (i = 0; i < process_num; i++) 
	{
		scanf("%s %d %d", proc[i].name, &proc[i].ready_time, &proc[i].exec_time);
		proc[i].Have_used_CPU = 0;
	}

	qsort(proc , process_num , sizeof(Process) , cmp);

	if (strcmp(_policy, "FIFO") == 0) {
		policy = FIFO;
	}
	else if (strcmp(_policy, "RR") == 0) {
		policy = RR;
	}
	else if (strcmp(_policy, "SJF") == 0) {
		policy = SJF;
	}
	else if (strcmp(_policy, "PSJF") == 0) {
		policy = PSJF;
	}
	else {
		fprintf(stderr, "Invalid policy: %s", _policy);
		exit(0);
	}

	scheduling(proc, process_num, policy);

	exit(0);
}
