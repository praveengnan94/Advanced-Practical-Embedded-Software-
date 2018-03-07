/***************************************************************
* AUTHOR  : Praveen Gnanasekaran
* DATE    : 03/06/2018
* DESCRIPTION  : This program explores various shared memory mechanism to communicate in Linux
* REFERENCE : https://linuxprograms.wordpress.com/2008/01/23/using-pipes-in-linux-programming/
* HEADER FILES  : q2.h
****************************************************************/

#include "q2.h"

typedef struct {
        char led_status[10];
        char message[50];
} msg_struct_pipes;

msg_struct_pipes actual_msg_pipes;

void pipes()
{
    printf("PIPES Example\n");

    msg_struct_pipes child_message[1];
    strcpy(child_message->message,"CHILD MESSAGE");
    strcpy(child_message->led_status,"LEDON");
    

    msg_struct_pipes parent_message[1];
    strcpy(parent_message->message,"PARENT MESSAGE");
    strcpy(parent_message->led_status,"LEDOFF");

    msg_struct_pipes* message_buf = (msg_struct_pipes*)malloc(sizeof(msg_struct_pipes));
    if(message_buf==NULL) 
    {
        printf("malloc Error: %s\n", strerror(errno)); 
        exit(1);
    }

    int file_desc[2];
    ret = pipe(file_desc);

    if (ret < 0) 
    {
        perror("pipe ");
        exit(1);
    }

    if (ret==-1) 
    {
        printf("Error: %s\n", strerror(errno)); 
        exit(1);
    }

    switch(fork()) {

    case -1://error in fork call
        printf("Error: %s\n", strerror(errno)); 
        break;

    case 0://child process(has 0 as return for fork) executes this
            
        printf("Child Process\n");
        ret =write(file_desc[1],
                   child_message,
                   sizeof(child_message[1]));

        if(ret == -1) 
        {
            perror("write");
            exit(2);
        }

        ret = read(file_desc[0],message_buf,50);
        if(ret == -1) 
        {
           perror("read");
           exit(3);
        }

        printf("CHILD SAYS:%s;led_status:%s\n",message_buf->message,message_buf->led_status);

        if(strcmp((message_buf->led_status),"LEDOFF")==0)
            system("echo 0 > /sys/class/leds/beaglebone:green:usr0/brightness");
        if(strcmp((message_buf->led_status),"LEDON")==0)
            system("echo 1 > /sys/class/leds/beaglebone:green:usr0/brightness");

        sleep(3);

        printf("Exit child\n");
        break;

    default://parent process(receives PID as return for fork) executes this
        printf("Parent Process,\n");

        ret = read(file_desc[0],message_buf,50);
        if(ret == -1) 
        {
           perror("read");
           exit(3);
        }

        printf("PARENT SAYS:%s;led_status:%s\n", message_buf->message,message_buf->led_status);

        if(strcmp((message_buf->led_status),"LEDOFF")==0)
            system("echo 0 > /sys/class/leds/beaglebone:green:usr0/brightness");
        if(strcmp((message_buf->led_status),"LEDON")==0)
            system("echo 1 > /sys/class/leds/beaglebone:green:usr0/brightness");

        sleep(3);

        ret =write(file_desc[1],
                   parent_message,
                   sizeof(parent_message[1]));
        if(ret == -1) 
        {
            perror("write");
            exit(2);
        }


        printf("Exit parent\n");
    }
}