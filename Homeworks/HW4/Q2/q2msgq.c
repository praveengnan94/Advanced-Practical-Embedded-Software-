#include "q2.h"

void msgq()
{

    printf("Messgae Que Example\n");
    /****variables used in each process*********/
    /***** after fork(), each process will have its own copy*****/
    struct mq_attr msgq_attr = {.mq_maxmsg = 10, //max # msg in queue
                                .mq_msgsize = BUF_SIZE,//max size of msg in bytes
                                .mq_flags = 0};
    mqd_t msgq;
    int msg_prio;
    int num_bytes;


    switch(fork()) {
    case -1://fork failed
            printf("Fork Error:%s\n",strerror(errno));
            return -1;
    case 0:        //child process receives message
            printf("Entering Child, PID:%d\n",getpid());
            sleep(1);//if child process runs first, this allows parent to be completed before
            msgq = mq_open(MY_MQ,
                           O_RDWR,
                           S_IRWXU, //non zero for O_CREAT flags
                           &msgq_attr);
            if(msgq < 0) { printf("mq_open Error:%s\n",strerror(errno)); return -1;}
            else printf("Messgae Que Opened by rxr\n");
            num_bytes=mq_receive(msgq,
                                 (char*)message_buf,
                                 BUF_SIZE,
                                 &msg_prio);
            if(num_bytes<0) {printf("mq_rcv Error:%s\n",strerror(errno)); return -1;}
            else {
                    printf("rxd in child:%s;led_status:%d\nlength:%d; priority:%d\n",
                           ((msg_struct*)message_buf)->message,
                           ((msg_struct*)message_buf)->led_status,
                           num_bytes,msg_prio);
            }
            num_bytes = mq_send(msgq,
                                (const char*)child_message,
                                sizeof(child_message),
                                msg_prio);
            if(num_bytes<0) {printf("mq_send Error:%s\n",strerror(errno)); return -1;}
            else printf("Message sent from child\n");


            break;


    default://parent process sends the message
            printf("Parent Process, PID:%d\n",getpid());
            msg_prio = 30;
            msgq = mq_open(MY_MQ, //name
                           O_CREAT | O_RDWR,//flags
                           S_IRWXU, //mode-read,write and execute permission
                           &msgq_attr); //attribute
            if(msgq < 0) { printf("mq_open Error:%s\n",strerror(errno)); return -1;}
            else printf("Messgae Que Opened by sender\n");
            num_bytes = mq_send(msgq,
                                (const char*)parent_message,
                                sizeof(parent_message),
                                msg_prio);
            if(num_bytes<0) {printf("mq_send Error:%s\n",strerror(errno)); return -1;}
            else printf("Message sent from parent\n");
            sleep(3);//allows child process to run and send msg
            num_bytes=mq_receive(msgq,
                                 (char*)message_buf,
                                 BUF_SIZE,
                                 &msg_prio);
            if(num_bytes<0) {printf("mq_rcv Error:%s\n",strerror(errno)); return -1;}
            else {
                    printf("rxd in parent:%s;led_status:%d\nlength:%d; priority:%d\n",
                           ((msg_struct*)message_buf)->message,
                           ((msg_struct*)message_buf)->led_status,
                           num_bytes,msg_prio);
            }


    }

    mq_unlink(MY_MQ);
}