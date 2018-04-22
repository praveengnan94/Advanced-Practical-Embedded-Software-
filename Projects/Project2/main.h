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
#include "AccelTask.c"
#include "MagnetoTask.c"
#include "LoggerTask.c"
#include "CommTask.c"


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

uint8_t accel_exit_flag = 0;
uint8_t magneto_exit_flag = 0;
uint8_t logger_exit_flag = 0;
uint8_t comm_exit_flag = 0;

int ret; 

void accel_heartbeat_handl(int sig) ;

void magneto_heartbeat_handl(int sig) ;

void logger_heartbeat_handl(int sig) ;

sig_atomic_t accel_heartbeat_flag;
sig_atomic_t logger_heartbeat_flag;
sig_atomic_t magneto_heartbeat_flag;
sig_atomic_t comm_heartbeat_flag;


