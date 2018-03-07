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
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/un.h>

#define PRINT_ERR(err) {printf("%s Error: %s\n",err, strerror(errno)); return -1;}

#define MY_MQ "/send_receive_mq"
#define PORT 8080
#define BUF_SIZE (4096) //max size for atomic read and write

typedef struct {
        uint8_t led_status;
        char message[BUF_SIZE - sizeof(uint8_t)];
} msg_struct;

int ret;

