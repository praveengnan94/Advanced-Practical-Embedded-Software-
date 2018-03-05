//https://linuxgazette.net/133/saha.html

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

int rc;
struct task_struct *task;
struct pid *pid_struct;

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Process tree");
MODULE_AUTHOR("Praveen");