/***************************************************************
* AUTHOR  : Praveen Gnanasekaran
* DATE    : 03/06/2018
* DESCRIPTION  : This program creates a thread program which creates two threads, and shares thread info using kfifo
* REFERENCE : https://linuxgazette.net/133/saha.html
* SOURCE FILES  : processtree.c
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

int rc;
struct task_struct *task;
struct pid *pid_struct;

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Process tree");
MODULE_AUTHOR("Praveen");