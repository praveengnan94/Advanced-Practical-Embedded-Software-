/***************************************************************
* AUTHOR  : Praveen Gnanasekaran
* DATE    : 04/28/2018
* DESCRITPTION  : CommTask.h
                  
* SOURCE FILES  : CommTask.c
****************************************************************/
#include "lsm9ds1.h"
#include "msgque.h"
#include "notify.h"
#include <arpa/inet.h>
#include <errno.h>
#include <fcntl.h>
#include <mqueue.h>
#include <netinet/in.h>
#include <pthread.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>
#include "uartServer.h"
#include "sockets.h"