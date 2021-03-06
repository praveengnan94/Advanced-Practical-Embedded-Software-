/***************************************************************
* AUTHOR  : Praveen Gnanasekaran
* DATE    : 04/28/2018
* DESCRITPTION  : main.h
                  
* SOURCE FILES  : main.c
****************************************************************/
#include <errno.h>
#include <mqueue.h>
#include <pthread.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdint.h>
#include <unistd.h>
#include "notify.h"
#include "MagnetoTask.c"
#include "AccelTask.c"
#include "LoggerTask.c"
#include "CommTask.c"

int i2c_glb_pass=1;

#define UNITERRUPTIBLE_SLEEP(t)                                                               \
  struct timespec current, remaining;                                          \
  current.tv_nsec = 0;                                                         \
  current.tv_sec = t;                                                          \
  do {                                                                         \
    ret = nanosleep(&current, &remaining);                                     \
    if (ret == -1) {                                                           \
      current.tv_sec = remaining.tv_sec;                                       \
      current.tv_nsec = remaining.tv_nsec;                                     \
    }                                                                          \
  } while (ret != 0);

char* fileid;
char killoption;

uint8_t magneto_exit_flag = 0;
uint8_t accel_exit_flag = 0;
uint8_t logger_exit_flag = 0;
uint8_t comm_exit_flag = 0;

int ret; 


void magneto_heartbeat_handl(int sig) ;

int magneto_heartbeat_flag;
int accel_heartbeat_flag;


