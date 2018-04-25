#include "LoggerTask.h"

void *LoggerTask(void *pthread_inf) {
	int ret,len_bytes;
	char buffer[BUFFER_SIZE];
	int priority;
	
	 struct mq_attr attr = {
					.mq_maxmsg = 16, 
                    .mq_msgsize = BUFFER_SIZE, 
                    .mq_flags = 0
				};

        mqd_t msg_queue;

	msg_queue = mq_open(ACCEL_MSGQ_IPC, O_RDWR , S_IRWXU,&attr);

	        if(msg_queue < 0) 
			{ 
				perror("ERROR:\n"); 
				return 0;
			}
			
	threadTaskAttr *pthread_info = (threadTaskAttr *)pthread_inf;

		
	 
	while(1)
	{
	   while (logger_flag_glb == 0) 
	    {
	      pthread_cond_wait(&cond_var_logger, &lock_logger);
	    }

	    logger_flag_glb = 0;
	    pthread_kill(pthread_info->main, LOGGER_SIG_HEARTBEAT);

	    len_bytes = mq_receive(msg_queue, (char*)buffer, BUFFER_SIZE, &priority);

	        if(len_bytes < 0) 
			{
				perror("Logger ERROR: \n");
				return 0;
			}

		        else 
			{
				printf("RECEIVED %s\n",buffer);
	        }

	}
	
}