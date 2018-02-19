/***************************************************************
* AUTHOR  : Praveen Gnanasekaran
* DATE    : 02/18/2018
* DESCRITPTION  : This program all definitions,macros and structure definitions
					for the parameters and libraries used in the program
      
* SOURCE FILES  : threads.c
* HEADER FILES  : customsignal.h, linkedlist.h
****************************************************************/

#define _GNU_SOURCE
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <sched.h>
#include <time.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <syscall.h>
#include <sys/types.h>
#include <signal.h>
#include "linkedlist.h"
#include "customsignal.h"

#define NUM_THREADS (3)
#define NUM_CPUS (1)

#define NSEC_PER_SEC (1000000000)
#define NSEC_PER_MSEC (1000000)
#define NSEC_PER_MICROSEC (1000)
#define DELAY_TICKS (1)
#define ERROR (-1)
#define OK (0)

char filestring[5000];

pid_t getpid(void);
pid_t gettid(void);
pthread_t threads[NUM_THREADS];
pthread_attr_t rt_sched_attr[NUM_THREADS];
int rt_max_prio, rt_min_prio;
struct sched_param rt_param[NUM_THREADS];
struct sched_param main_param;
pthread_attr_t main_attr;
pid_t mainpid;
pthread_mutex_t mutexlock;
pthread_mutexattr_t mutexattr;
int rc;

/*Struct for threadinfo*/
typedef struct threadinfo
{
	char logfilename[20];	
	pthread_t pid;
	pid_t tid;
}threadinf;


