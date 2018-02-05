/***************************************************************
* AUTHOR	: Praveen Gnanasekaran
* DATE		: 02/03/2018
* DESCRIPTION	: This program contains all the library functions and macro definitions for 	
					praveentimer.c file
		  
* SOURCE FILES	: praveentimer.c
****************************************************************/

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/timer.h>
#include <linux/init.h>	

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Timer module");
MODULE_AUTHOR("Praveen");

static struct timer_list pravtimer;
