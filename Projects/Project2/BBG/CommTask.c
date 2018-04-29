#include "CommTask.h"

void *CommTask(void *pthread_inf) {

	int priority, len_bytes,ret;
	
	uartstructre *uartstructnew=(uartstructre *)malloc(sizeof(uartstructre ));

	char data_cel_str[BUFFER_SIZE - 200];
  float data_cel;

  
        struct mq_attr attr = {
				                .mq_maxmsg = 16, 
                                .mq_msgsize = BUFFER_SIZE, 
                                .mq_flags = 0
				};

    mqd_t msg_queue;

     msg_queue = mq_open(COMM_MSGQ_IPC, O_RDWR | O_CREAT, S_IRWXU, &attr);

        if(msg_queue < 0) 
		{ 
			perror("ERROR:\n"); 
			return 0;
		}

	uartinit();
	while(1)
	{
		ret=uartRead(uartstructnew);

    logger_pckt comm_log = {.log_level = 1};

    sprintf(data_cel_str, "%d\n %d\n %f\n %f\n", uartstructnew->clientid,uartstructnew->clientinfo,uartstructnew->uv_payload, uartstructnew->pr_payload);

    strcpy(comm_log.log_msg, data_cel_str);


    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    strcpy(comm_log.time_stamp, asctime(tm));
    clock_gettime(CLOCK_MONOTONIC, &current);
    expire.tv_sec = current.tv_sec + 2;
    expire.tv_nsec = current.tv_nsec;

len_bytes = mq_send(msg_queue,(const char *)&comm_log,sizeof(logger_pckt), (unsigned int )MESSAGE_PRIORITY);
		        if(len_bytes < 0) 
			{
				printf("ERROR: child_to_parent message sending fail\n"); 
				return 0;
			}
		        else
		        {} 
	}
}