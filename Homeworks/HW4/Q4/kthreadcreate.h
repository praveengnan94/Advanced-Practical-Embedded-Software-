/***************************************************************
* AUTHOR  : Praveen Gnanasekaran
* DATE    : 03/06/2018
* DESCRIPTION  : This program creates a thread program which creates two threads, and shares thread info using kfifo
* REFERENCE : https://sysplay.in/blog/tag/kernel-threads/
* SOURCE FILES  : kthreadcreate.c
****************************************************************/

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

/* fifo size in elements (bytes) */
#define FIFO_SIZE	128

typedef STRUCT_KFIFO_REC_1(FIFO_SIZE) mytest;

char buf[100];
unsigned int ret;
static mytest test;

static DEFINE_MUTEX(mutexlock);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Kthread create");
MODULE_AUTHOR("Praveen");