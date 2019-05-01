#ifndef _SCHEDULING_H_
#define _SCHEDULING_H_

#include "process.h"

#define FIFO	1
#define RR	2
#define SJF	3
#define PSJF	4

/* Return next process to run */
//int next_process(Process *proc, int nproc, int policy);

/* Running scheduler */
int scheduling(Process *proc, int nproc, int policy);

#endif
