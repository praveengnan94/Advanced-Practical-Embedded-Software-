//https://sysplay.in/blog/tag/kernel-threads/

#include "kthreadcreate.h"

static struct task_struct *thread_st1;
static struct task_struct *thread_st2;


static int thread_two(void *unused)
{

    printk(KERN_INFO "record fifo test start\n");

    while (!kthread_should_stop())
    {
        /* put in variable length data */
        strcpy(buf,"SOMEMESSAGE");
        kfifo_in(&test, buf, strlen(buf));

        /* show the first record without removing from the fifo */
        ret = kfifo_out_peek(&test, buf, sizeof(buf));
        if (ret)
        {
            printk(KERN_INFO "%.*s\n", ret, buf);
        }

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
            printk(KERN_INFO "Thread 1 Running\n");
            ret = kfifo_out(&test, buf, sizeof(buf));
            buf[ret] = '\0';
            printk(KERN_INFO "item = %.*s\n", ret, buf);
            printk(KERN_INFO "test passed\n");

        }
        
        // ssleep(5);
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

    // rc= pthread_mutex_init(&mutexlock,&mutexattr);
    // if(rc!=0)
    // {
    //   perror("MUTEX ERROR ");
    // }

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

   // pthread_mutex_t mutexlock;
   // pthread_mutexattr_t mutexattr;
}

module_init(init_thread);
module_exit(cleanup_thread);