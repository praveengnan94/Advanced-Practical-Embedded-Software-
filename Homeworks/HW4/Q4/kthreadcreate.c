/***************************************************************
* AUTHOR  : Praveen Gnanasekaran
* DATE    : 03/06/2018
* DESCRIPTION  : This program creates a thread program which creates two threads, and shares thread info using kfifo
* REFERENCE : https://sysplay.in/blog/tag/kernel-threads/
* HEADER FILES  : kthreadcreate.h
****************************************************************/

#include "kthreadcreate.h"

static struct task_struct *thread_st1;
static struct task_struct *thread_st2;


static int thread_two(void *unused)
{
    char prevpid[50], currentpid[50], nextpid[50];
    printk(KERN_INFO "record fifo test start\n");

    while (!kthread_should_stop())
    {
        printk(KERN_INFO "Thread 1 Running\n");
        

        sprintf(prevpid, "Previous PID: %d, vruntime: %llu\n", list_prev_entry(current, tasks)->pid, 
                                        list_prev_entry(current, tasks)->se.vruntime);

        sprintf(currentpid, "Current PID: %d, vruntime: %llu\n",  current->pid, 
                                    current->se.vruntime);

        sprintf(nextpid, "Next PID: %d, vruntime: %llu\n",     list_next_entry(current, tasks)->pid, 
                                    list_next_entry(current, tasks)->se.vruntime  );

        mutex_lock(&mutexlock);

        /* put in variable length data */
        kfifo_in(&test, prevpid, strlen(prevpid));
        kfifo_in(&test, currentpid, strlen(currentpid));
        kfifo_in(&test, nextpid, strlen(nextpid));

        mutex_unlock(&mutexlock);

        printk(KERN_INFO "fifo len: %u\n", kfifo_len(&test));
        
        ssleep(3);
    }

    printk(KERN_INFO "Second Thread Stopping\n");
    do_exit(0);
    return 0;
}

// Function executed by kernel thread
static int thread_one(void *unused)
{

    while (!kthread_should_stop())
    {
        
        /* check the correctness of all values in the fifo */
        while (!kfifo_is_empty(&test)) {
            printk(KERN_INFO "Thread 2 Running\n");
            mutex_lock(&mutexlock);
            ret = kfifo_out(&test, buf, sizeof(buf));
            mutex_unlock(&mutexlock);
            buf[ret] = '\0';
            printk(KERN_INFO "%.*s\n", ret, buf);
            printk(KERN_INFO "test passed\n");

        }
    }

    printk(KERN_INFO "First Thread Stopping\n");
    do_exit(0);
    return 0;   
    
}

// Module Initialization
static int __init init_thread(void)
{
    INIT_KFIFO(test);

    printk(KERN_INFO "Creating Thread\n");
    
    thread_st1 = kthread_create(thread_one, NULL, "mythreadone");
    if (thread_st1)
    {
        printk("Thread 1 Created successfully\n");
        wake_up_process(thread_st1);
    }
    else
        printk(KERN_INFO "Thread 1 creation failed\n");

    thread_st2 = kthread_create(thread_two, NULL, "mythreadtwo");
    if (thread_st2)
    {
        printk("Thread 2 Created successfully\n");
        wake_up_process(thread_st2);
    }
    else
        printk(KERN_INFO "Thread 2 creation failed\n");

    return 0;
}
// Module Exit
static void __exit cleanup_thread(void)
{
    printk("Cleaning Up\n");
    if (thread_st1)
   {
       kthread_stop(thread_st1);
       printk(KERN_INFO "Thread 1 stopped");
   }
   if (thread_st2)
   {
       kthread_stop(thread_st2);
       printk(KERN_INFO "Thread 2 stopped");
   }

}

module_init(init_thread);
module_exit(cleanup_thread);