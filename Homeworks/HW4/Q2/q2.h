#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <mqueue.h>
#include <sys/un.h>
#include <netinet/in.h>

typedef unsigned char     uint8_t;
typedef unsigned short    uint16_t;
typedef unsigned int      uint32_t;
typedef unsigned long int uint64_t;


#define MY_MsgQue "/send_receive_mq"

int ret; 
#define PORT 8080

#define ADDRESS     "socket"  /* addr to connect */