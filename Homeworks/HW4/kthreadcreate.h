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

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Kthread create");
MODULE_AUTHOR("Praveen");