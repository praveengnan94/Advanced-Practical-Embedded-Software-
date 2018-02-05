/***************************************************************
* AUTHOR	: Praveen Gnanasekaran
* DATE		: 01/29/2018
* DESCRIPTION	: This program does a system call to sort array from user to
					kernel space and then back to user space
		  
* SOURCE FILES	: testf.c
****************************************************************/

#define _GNU_SOURCE

#include <stdio.h>
#include <stdint.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <stdlib.h>     
#include <time.h>

#define BUFFER_DEPTH 256
#define TOTAL_CALLS 3	//to invoke the system call numerous times