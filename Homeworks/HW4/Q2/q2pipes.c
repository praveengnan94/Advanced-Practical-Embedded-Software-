// https://linuxprograms.wordpress.com/2008/01/23/using-pipes-in-linux-programming/

#include "q2.h"

typedef struct {
        uint8_t led_status;
        char message[50];
} msg_struct_pipes;

msg_struct_pipes actual_msg_pipes;


void pipes()
{
    printf("PIPES Example\n");

    /*linux has Half duplex setting, thus file_descriptor[0] is always used for reading,file_descriptor[1] always used for writing*/
    msg_struct_pipes child_message[1];
    strcpy(child_message->message,"LEDON");
    child_message->led_status = 0;

    msg_struct_pipes parent_message[1];
    strcpy(parent_message->message,"LEDOFF");
    parent_message->led_status = 1;

    msg_struct_pipes* message_buf = (msg_struct_pipes*)malloc(sizeof(msg_struct_pipes));
    if(message_buf==NULL) 
    {
        printf("malloc Error: %s\n", strerror(errno)); 
        exit(1);
    }


    int file_descriptor[2];
    ret = pipe(file_descriptor);

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
        //close(file_descriptor[0]);
        ret =write(file_descriptor[1],
                   child_message,
                   sizeof(child_message[1]));

        if(ret == -1) 
        {
            perror("write");
            exit(2);
        }

        sleep(1);

        ret = read(file_descriptor[0],message_buf,50);
        if(ret == -1) 
        {
           perror("read");
           exit(3);
        }

        printf("Message received by child:%s;led_status:%d\n",message_buf->message,message_buf->led_status);

        close(file_descriptor[0]); 
        close(file_descriptor[1]);

        printf("Exit child\n");
        break;

    default://parent process(receives PID as return for fork) executes this
        printf("Parent Process,\n");

        ret = read(file_descriptor[0],message_buf,50);
        if(ret == -1) 
        {
           perror("read");
           exit(3);
        }

        printf("Message received by parent:%s;led_status:%d\n", message_buf->message,message_buf->led_status);

        ret = write(file_descriptor[1],parent_message,sizeof(parent_message[1]));
        if(ret == -1) 
        {
            perror("write");
            exit(2);
        }

        sleep(1);

        close(file_descriptor[0]); 
        close(file_descriptor[1]);
        printf("Exit parent\n");
    }
}