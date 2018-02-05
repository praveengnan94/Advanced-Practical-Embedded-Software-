/***************************************************************
* AUTHOR	: Praveen Gnanasekaran
* DATE		: 01/31/2018
* DESCRIPTION	: This program contains header files and definition libraries for cronjob.c
		  
* SOURCE FILES	: mycronjob.c
****************************************************************/

#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/stat.h> 
#include <fcntl.h> //file system calls
#include <string.h>
#include <time.h>
#include <stdint.h>
#include <sys/time.h>

#define BUFFER_SIZE 256

struct timeval tv;
struct tm* ptm;
