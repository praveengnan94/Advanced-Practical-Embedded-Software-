/***************************************************************
* AUTHOR  : Praveen Gnanasekaran
* DATE    : 04/28/2018
* DESCRITPTION  : LoggerTask.h
                  
* SOURCE FILES  : LoggerTask.c
****************************************************************/
#include <errno.h>
#include <mqueue.h>
#include <pthread.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "msgque.h"

#define UV_ALIVE 1
#define PR_ALIVE 4

extern int i2c_glb_pass;

long int ledcount,ledcount2;