/***************************************************************
* AUTHOR	: Praveen Gnanasekaran
* DATE		: 02/03/2018
* DESCRIPTION	: This program creates a custom timer module which can be defaulted to 
					a certain username and time or can be changed
		  
* HEADER FILES	: praveentimer.h
****************************************************************/

#include "praveentimer.h"

static char *myname="Praveen";
static int default_time=500;
static int cnt=0; //kepe track of the number of times the timer module is fired

//channge module params
module_param(myname,charp,S_IRUGO);
module_param(default_time,int,S_IRUGO);

void prav_timer_callback(unsigned long data)
{
	int rt;
	cnt++;
	printk(KERN_INFO "prav_timer_callback function called successfully");
	printk(KERN_INFO "Count : %d Name: %s",cnt,myname );

	rt = mod_timer(&pravtimer, jiffies+msecs_to_jiffies(default_time));

	if(rt==1)
		printk(KERN_INFO "Error calling mod_timer");
}


int __init timer_mod_init(void)
{
	int rt;
	setup_timer( &pravtimer , prav_timer_callback , 0);
	printk(KERN_INFO "Setup timer called");

	rt=mod_timer(&pravtimer, jiffies+msecs_to_jiffies(default_time));


	if(rt==1)
		printk(KERN_INFO "Error calling mod_timer");

	return 0;
}

void __exit timer_mod_exit(void)
{
	del_timer(&pravtimer);
	printk(KERN_INFO "Timer Exit");
}

module_init(timer_mod_init);
module_exit(timer_mod_exit);