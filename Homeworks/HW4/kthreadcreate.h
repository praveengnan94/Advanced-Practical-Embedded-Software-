#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/delay.h>
#include <linux/sched.h>   //wake_up_process()
#include <linux/kthread.h> //kthread_create(), kthread_run()

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Kthread create");
MODULE_AUTHOR("Praveen");