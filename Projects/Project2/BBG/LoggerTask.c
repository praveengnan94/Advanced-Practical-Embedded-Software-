/***************************************************************
* AUTHOR  : Praveen Gnanasekaran
* DATE    : 04/28/2018
* DESCRITPTION  : LoggerTask.c
                  
* HEADER FILES  : LoggerTask.h
****************************************************************/
#include "LoggerTask.h"

typedef struct{
	uint32_t clientid;
	uint32_t clientinfo;
	float uv_payload;
	float pr_payload;
}uartstructrelog;

// extern int accel_heartbeat_flag;
extern uint8_t magneto_exit_flag;
void *LoggerTask(void *pthread_inf) {
	int ret,len_bytes;
	char buffer[BUFFER_SIZE];
	int priority;

	logger_pckt *log = (logger_pckt *)malloc(sizeof(logger_pckt));
	logger_pckt *log_comm = (logger_pckt *)malloc(sizeof(logger_pckt));
	
	 struct mq_attr attr = {
					.mq_maxmsg = 16, 
                    .mq_msgsize = BUFFER_SIZE, 
                    .mq_flags = 0
				};

        mqd_t msg_queue,msg_queue_comm,msg_queue2;

	msg_queue = mq_open(ACCEL_MSGQ_IPC, O_RDWR , S_IRWXU,&attr);

	        if(msg_queue < 0) 
			{ 
				perror("ERROR:\n"); 
				return 0;
			}

	msg_queue2 = mq_open(MAGNETO_MSGQ_IPC, O_RDWR , S_IRWXU,&attr);

	        if(msg_queue2 < 0) 
			{ 
				perror("ERROR:\n"); 
				return 0;
			}

	msg_queue_comm = mq_open(COMM_MSGQ_IPC, O_RDWR , S_IRWXU,&attr);

	        if(msg_queue < 0) 
			{ 
				perror("ERROR:\n"); 
				return 0;
			}
			
	threadTaskAttr *pthread_info = (threadTaskAttr *)pthread_inf;
	
  char *fileid="logfile.txt";
  FILE *pfd = fopen(fileid, "w");
  if (pfd == NULL) 
  {
    perror("Log Task fopen ERROR");
  } 
  else{}
	 
	while(magneto_exit_flag==0)
	{
	    len_bytes = mq_receive(msg_queue, (char *)log, BUFFER_SIZE, &priority);

		if(len_bytes < 0) 
		{
			perror("Logger ERROR: \n");
			return 0;
		}

		else 
		{
			if ((magneto_heartbeat_flag==1)&&(i2c_glb_pass==1))
			{
				ledcount++;
				if(ledcount%2==0)
					LED_OFF;
				else
					LED_ON;
				fprintf(pfd, "TIME: %s  LEVEL: 1 SOURCE: MAGNTEOMETER: %s MAG ALIVE\n\n", ((logger_pckt *)log)->time_stamp, ((logger_pckt *)log)->log_msg);
				printf("TIME: %s  LEVEL: 1 SOURCE: MAGNTEOMETER: %s MAG ALIVE\n\n", ((logger_pckt *)log)->time_stamp, ((logger_pckt *)log)->log_msg);
				magneto_heartbeat_flag = 0;
			}
			else 
			{
				fprintf(pfd, "TIME: %s  LEVEL: 2 SOURCE: MAGNTEOMETER: MAG DEAD\n\n", ((logger_pckt *)log)->time_stamp);
				printf("TIME: %s  LEVEL: 2 SOURCE: MAGNTEOMETER: MAG DEAD\n\n", ((logger_pckt *)log)->time_stamp);
			}

			fflush(pfd);
        }


        len_bytes = mq_receive(msg_queue2, (char *)log, BUFFER_SIZE, &priority);

		if(len_bytes < 0) 
		{
			perror("Logger ERROR: \n");
			return 0;
		}

		else 
		{
			if ((accel_heartbeat_flag==1)&&(i2c_glb_pass==1))
			{
				ledcount2++;
				if(ledcount2%2==0)
					LED_OFF2;
				else
					LED_ON2;
				fprintf(pfd, "TIME: %s  LEVEL: 1 SOURCE: ACCELEROMETER: %s ACCEL ALIVE\n\n", ((logger_pckt *)log)->time_stamp, ((logger_pckt *)log)->log_msg);
				printf("TIME: %s  LEVEL: 1 SOURCE: ACCELEROMETER: %s ACCEL ALIVE\n\n", ((logger_pckt *)log)->time_stamp, ((logger_pckt *)log)->log_msg);
				accel_heartbeat_flag = 0;
			}
			else 
			{
				fprintf(pfd, "TIME: %s  LEVEL: 2 SOURCE: ACCELEROMETER: ACCEL DEAD\n\n", ((logger_pckt *)log)->time_stamp);
				printf("TIME: %s  LEVEL: 2 SOURCE: ACCELEROMETER: ACCEL DEAD\n\n", ((logger_pckt *)log)->time_stamp);
			}

			fflush(pfd);
        }

    	len_bytes = mq_receive(msg_queue_comm, (char *)log_comm, BUFFER_SIZE, &priority);

	        if(len_bytes < 0) 
			{
				perror("Logger ERROR: \n");
				return 0;
			}

	        else 
			{
				char strtemp[26];
				memcpy(strtemp,(void*)(logger_pckt *)(log_comm->log_msg),26);
				char *tok1,*tok2,*tok3,*tok4;

				tok1=strtok(strtemp,"\n");
				tok2=strtok(NULL,"\n");
				tok3=strtok(NULL,"\n");
				tok4=strtok(NULL,"\n");

				int clientstatus=atoi(tok2);
				    
				if(clientstatus&UV_ALIVE)
				{
					fprintf(pfd, "TIME: %s  LEVEL: 1 SOURCE: TIVA ID: %s UV ALIVE %s [UVI]\n\n", ((logger_pckt *)log_comm)->time_stamp, tok1,tok3);
					printf("TIME: %s  LEVEL: 1 SOURCE: TIVA ID: %s UV ALIVE %s [UVI]\n\n", ((logger_pckt *)log_comm)->time_stamp, tok1,tok3);
				}
				else 
				{
					fprintf(pfd, "TIME: %s  LEVEL: 2 SOURCE: TIVA ID: %s UV DEAD\n\n", ((logger_pckt *)log_comm)->time_stamp, tok1);
					printf("TIME: %s  LEVEL: 2 SOURCE: TIVA ID: %s UV DEAD\n\n", ((logger_pckt *)log_comm)->time_stamp, tok1);
				}
				if(clientstatus&PR_ALIVE)
				{
					fprintf(pfd, "TIME: %s  LEVEL: 1 SOURCE: TIVA ID: %s PR ALIVE %s [kPa]\n\n", ((logger_pckt *)log_comm)->time_stamp, tok1,tok4);
					printf("TIME: %s  LEVEL: 1 SOURCE: TIVA ID: %s PR ALIVE %s [kPa]\n\n", ((logger_pckt *)log_comm)->time_stamp, tok1,tok4);
				}
				else 
				{
					fprintf(pfd, "TIME: %s  LEVEL: 2 SOURCE: TIVA ID: %s PR DEAD\n\n", ((logger_pckt *)log_comm)->time_stamp, tok1);
					printf("TIME: %s  LEVEL: 2 SOURCE: TIVA ID: %s PR DEAD\n\n", ((logger_pckt *)log_comm)->time_stamp, tok1);
				}
				
        		fflush(pfd);
	        }

	}
	
}