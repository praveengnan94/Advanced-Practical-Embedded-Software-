#include "kthreadcreate.h"

static struct task_struct *thread_st;


static int __init testfunc(void)
{
    char        buf[100];
    unsigned int    ret;
    struct { unsigned char buf[6]; } hello = { "hello" };

    printk(KERN_INFO "record fifo test start\n");

    kfifo_in(&test, &hello, sizeof(hello));

    /* show the size of the next record in the fifo */
    printk(KERN_INFO "fifo peek len: %u\n", kfifo_peek_len(&test));

    /* put in variable length data */
    strcpy(buf,"SOMEMESSAGE");
    kfifo_in(&test, buf, strlen(buf));

    /* skip first element of the fifo */
    printk(KERN_INFO "skip 1st element\n");
    kfifo_skip(&test);

    printk(KERN_INFO "fifo len: %u\n", kfifo_len(&test));

    /* show the first record without removing from the fifo */
    ret = kfifo_out_peek(&test, buf, sizeof(buf));
    if (ret)
        printk(KERN_INFO "%.*s\n", ret, buf);

    /* check the correctness of all values in the fifo */
    while (!kfifo_is_empty(&test)) {
        ret = kfifo_out(&test, buf, sizeof(buf));
        buf[ret] = '\0';
        printk(KERN_INFO "item = %.*s\n", ret, buf);
    }
    printk(KERN_INFO "test passed\n");

    return 0;
}

// Function executed by kernel thread
static int thread_fn(void *unused)
{
    while (!kthread_should_stop())
    {
        printk(KERN_INFO "Thread Running\n");
        ssleep(5);
    }
    printk(KERN_INFO "Thread Stopping\n");
    do_exit(0);
    return 0;
}

// Module Initialization
static int __init init_thread(void)
{
    INIT_KFIFO(test);

    if (testfunc() < 0) {
        return -EIO;
    }

    printk(KERN_INFO "Creating Thread\n");
    //Create the kernel thread with name 'mythread'
    thread_st = kthread_create(thread_fn, NULL, "mythread");
    if (thread_st)
    {
        printk("Thread Created successfully\n");
        wake_up_process(thread_st);
    }
    else
        printk(KERN_INFO "Thread creation failed\n");
    return 0;
}
// Module Exit
static void __exit cleanup_thread(void)
{
    printk("Cleaning Up\n");
    // remove_proc_entry(PROC_FIFO, NULL);
    if (thread_st)
   {
       kthread_stop(thread_st);
       printk(KERN_INFO "Thread stopped");
   }
}

module_init(init_thread);
module_exit(cleanup_thread);