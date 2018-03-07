/***************************************************************
* AUTHOR  : Praveen Gnanasekaran
* DATE    : 03/06/2018
* DESCRIPTION  : This program creates a thread program which creates two threads, and shares thread info using kfifo
* REFERENCE : https://linuxgazette.net/133/saha.html
* HEADER FILES  : processtree.h
****************************************************************/

#include "processtree.h"

int mypid = -1;
module_param(mypid, int, S_IRUGO); // passing parameters to the module

int iterate_child(struct list_head *child)
{
	int childcount = 0;
	struct list_head *p;
			
   //list_for_each() iterates over a list from the beginning to the end of the list
	list_for_each(p, child){
		childcount++;
	}

	return childcount;
}

int __init process_init(void)
{
	printk(KERN_INFO "Entering process module");

	if(mypid == -1)
		task = current;
	else
	{
		pid_struct = find_get_pid(mypid);
		task = pid_task(pid_struct, PIDTYPE_PID);
	}

	for(task=task; task!=&init_task; task=task->parent)	//current is a macro which points to the current task / process
	{
		printk("Thread name: %s,Process ID: %d, Process status: %ld, Number of children: %d, Nice value: %d \n",task->comm,task->pid, task->state,iterate_child(&task->children),task_nice(task)); 			// returns nice value of task
	}

	return 0;
}

void __exit process_exit(void)
{

	printk(KERN_INFO "Cleaning process module");
}

module_init(process_init);
module_exit(process_exit);
