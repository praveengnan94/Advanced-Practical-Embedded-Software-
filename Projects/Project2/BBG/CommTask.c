/***************************************************************
* AUTHOR  : Praveen Gnanasekaran
* DATE    : 04/28/2018
* DESCRITPTION  : CommTask.c
                  
* HEADER FILES  : CommTask.h
****************************************************************/

#include "CommTask.h"
#define SOCKET 

extern uint8_t magneto_exit_flag;
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
#ifdef SOCKET
		int num_char;
  int listenfd = 0, connfd = 0;
    struct sockaddr_in serv_addr; 

    char sendBuff[1025];
    time_t ticks; 

    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    memset(&serv_addr, '0', sizeof(serv_addr));
    memset(sendBuff, '0', sizeof(sendBuff)); 

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(5000); 

    bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)); 

    listen(listenfd, 10); 
    connfd = accept(listenfd, (struct sockaddr*)NULL, NULL); 
while(magneto_exit_flag==0)
{

	num_char = read(connfd, sendBuff, sizeof(sendBuff));
    if (num_char < 0) 
    {
      break;
    }
    uartstructnew=(uartstructre *)sendBuff;
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
#else
	CONFIG_UART_P924;
  CONFIG_UART_P926;
	uartinit();
	while(magneto_exit_flag==0)
	{
		ret=uartRead(uartstructnew);
		if(ret<0)
			printf("UART READ FAILED\n");
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
		        {
		        	// printf("QUUE SENT\n");
		        } 
	}
#endif
}