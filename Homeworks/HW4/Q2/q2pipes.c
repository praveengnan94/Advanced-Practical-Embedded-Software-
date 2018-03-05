#include "q2.h"

void pipes()
{
    printf("PIPES Example\n");
    int file_descriptor[2];
    ret = pipe(file_descriptor);
    if (ret==-1) {printf("Error: %s\n", strerror(errno)); return -1;}
    switch(fork()) {

    case -1://error in fork call
            printf("Error: %s\n", strerror(errno)); return -1;
            break;
    case 0://child process(has 0 as return for fork) executes this
            printf("Child Process, PID:%d\n",getpid());
            //close(file_descriptor[0]);
            ret =write(file_descriptor[1],
                       child_message,
                       sizeof(child_message));
            if(ret == -1) {printf("Message Not sent\n"); return -1;}
            else printf("Message Sent from child\n");
            sleep(1);
            ret = read(file_descriptor[0],message_buf,BUF_SIZE);
            if(ret == -1) {printf("Message Not rxd\n"); return -1;}
            else printf("Messag rxd in child:%s;led_status:%d\n",
                        message_buf->message,message_buf->led_status);
            close(file_descriptor[0]); close(file_descriptor[1]);
            printf("Exit child\n");
            break;

    default://parent process(receives PID as return for fork) executes this
            printf("Parent Process, PID:%d\n",getpid());

            ret = read(file_descriptor[0],message_buf,BUF_SIZE);
            if(ret == -1) {printf("Message Not rxd\n"); return -1;}
            else printf("Messag rxd in parent:%s;led_status:%d\n",
                        message_buf->message,message_buf->led_status);

            ret = write(file_descriptor[1],parent_message,sizeof(parent_message));
            if(ret == -1) {printf("Message Not sent\n"); return -1;}
            else printf("Message Sent from parent\n");
            sleep(1);
            close(file_descriptor[0]); close(file_descriptor[1]);
            printf("Exit parent\n");


    }
}