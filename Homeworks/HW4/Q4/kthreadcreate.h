#define _GNU_SOURCE
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/delay.h>
#include <linux/sched.h>   //wake_up_process()
#include <linux/kthread.h> //kthread_create(), kthread_run()
#include <linux/init.h>
#include <linux/proc_fs.h>
#include <linux/mutex.h>
#include <linux/kfifo.h>
// #include <pthread.h>
// #include <stdlib.h>
// #include <stdio.h>
// #include <sched.h>
// #include <time.h>
// #include <string.h>
// #include <errno.h>
// #include <unistd.h>
// #include <syscall.h>
// #include <sys/types.h>
// #include <signal.h>

/* fifo size in elements (bytes) */
#define FIFO_SIZE	128

typedef STRUCT_KFIFO_REC_1(FIFO_SIZE) mytest;

char buf[100];
unsigned int ret;
static mytest test;

// pthread_mutex_t mutexlock;
// pthread_mutexattr_t mutexattr;
int rc;

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Kthread create");
MODULE_AUTHOR("Praveen");