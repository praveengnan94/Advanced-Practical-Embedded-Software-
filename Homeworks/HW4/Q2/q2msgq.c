/***************************************************************
* AUTHOR  : Praveen Gnanasekaran
* DATE    : 03/06/2018
* DESCRIPTION  : This program explores various IPC SOCKET mechanism to communicate in Linux
* REFERENCE : https://users.cs.cf.ac.uk/Dave.Marshall/C/node25.html
* HEADER FILES  : q2.h
****************************************************************/

#include "q2.h"

#define BUFFER_SIZE (1024)

typedef struct {
        char led_status[10];
        char message[10];
} msg_struct_qu;

msg_struct_qu actual_msg_qu;

void msgq()
{
    struct mq_attr msgq_attr = {.mq_maxmsg = 5, //max # msg in queue
                                .mq_msgsize = BUFFER_SIZE,//max size of msg in bytes
                                .mq_flags = 0};
    mqd_t msgq;
    int msg_priority;
    int n;

    msg_struct_qu child_message[1];
    strcpy(child_message->message,"CHILD");
    strcpy(child_message->led_status,"LEDON");
    
    msg_struct_qu parent_message[1];
    strcpy(parent_message->message,"PARENT");
    strcpy(parent_message->led_status,"LEDOFF");
    
    msg_struct_qu* message_buf = (msg_struct_qu*)malloc(sizeof(msg_struct_qu));
    if(message_buf==NULL) 
    {
        printf("malloc Error: %s\n", strerror(errno)); 
        exit(1);
    }

    switch(fork()) {
    case -1://fork failed
            printf("Fork Error:%s\n",strerror(errno));
            exit(1);

    case 0:        //child process receives message
            msgq = mq_open(MY_MsgQue, O_RDWR, S_IRWXU, &msgq_attr);

            if(msgq < 0) 
            { 
                printf("mq_open Error:%s\n",strerror(errno)); 
                exit(1);
            }
            else 
                printf("Message opened by child\n");

            n=mq_receive(msgq, (char*)message_buf, BUFFER_SIZE, &msg_priority);

            if(n<0) 
            {
                printf("mq_rcv Error:%s\n",strerror(errno)); 
                exit(1);
            }
            else {
                printf("PARENT SAYS:%s;led_status:%s\n", ((msg_struct_qu*)message_buf)->message,((msg_struct_qu*)message_buf)->led_status);

                if(strcmp((((msg_struct_qu*)message_buf)->led_status),"LEDOFF")==0)
                    system("echo 0 > /sys/class/leds/beaglebone:green:usr0/brightness");
                if(strcmp((((msg_struct_qu*)message_buf)->led_status),"LEDON")==0)
                    system("echo 1 > /sys/class/leds/beaglebone:green:usr0/brightness");


            }
            n = mq_send(msgq, (const char*)child_message,BUFFER_SIZE,msg_priority);

            if(n<0) 
            {
                printf("mq_send Error:%s\n",strerror(errno)); 
                exit(1);
            }
            else 
                printf("Message sent from child\n");

            break;

    default://parent process sends the message
            msg_priority = 3;
            msgq = mq_open(MY_MsgQue, O_CREAT | O_RDWR, S_IRWXU,  &msgq_attr); 

            if(msgq < 0) 
            { 
                printf("mq_open Error:%s\n",strerror(errno)); 
                exit(1);
            }

            else 
                printf("Message Opened by sender\n");

            n = mq_send(msgq,(const char*)parent_message, BUFFER_SIZE, msg_priority);

            if(n<0) 
            {
                printf("mq_send Error:%s\n",strerror(errno)); 
                exit(1);
            }
            else 
                printf("Message sent from parent\n");

            sleep(3);//allows child process to run and send msg
            n=mq_receive(msgq,(char*)message_buf,BUFFER_SIZE, &msg_priority);

            if(n<0) 
            {
                printf("mq_rcv Error:%s\n",strerror(errno)); 
                exit(1);
            }
            else {
                printf("CHILD SAYS:%s;led_status:%s\n", ((msg_struct_qu*)message_buf)->message,((msg_struct_qu*)message_buf)->led_status);

                if(strcmp((((msg_struct_qu*)message_buf)->led_status),"LEDOFF")==0)
                    system("echo 0 > /sys/class/leds/beaglebone:green:usr0/brightness");
                if(strcmp((((msg_struct_qu*)message_buf)->led_status),"LEDON")==0)
                    system("echo 1 > /sys/class/leds/beaglebone:green:usr0/brightness");
            }
    }

    mq_unlink(MY_MsgQue);
}