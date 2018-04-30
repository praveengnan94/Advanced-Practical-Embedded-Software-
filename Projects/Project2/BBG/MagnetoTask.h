/***************************************************************
* AUTHOR  : Praveen Gnanasekaran
* DATE    : 04/28/2018
* DESCRITPTION  : MagnteoTask.h
                  
* SOURCE FILES  : MagnteoTask.c
****************************************************************/
#include <errno.h>
#include <mqueue.h>
#include <pthread.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "lsm9ds1.h"
#include "msgque.h"
#include <math.h>
#include "threads.h"
#include "loggerstructs.h"

struct timespec current, expire;
int num_bytes;
char data_cel_str[BUFFER_SIZE - 200];