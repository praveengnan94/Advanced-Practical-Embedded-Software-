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
	logger_pckt *log = (logger_pckt *)malloc(sizeof(logger_pckt));
  char *fileid="logfile.txt";
  FILE *pfd = fopen(fileid, "w");
  if (pfd == NULL) 
  {
    perror("Log Task fopen ERROR");
  } 
  else{}
	 
	while(1)
	{
	    len_bytes = mq_receive(msg_queue, (char *)log, BUFFER_SIZE, &priority);

	        if(len_bytes < 0) 
			{
				perror("Logger ERROR: \n");
				return 0;
			}

		        else 
			{
				fprintf(pfd, "TIME: %s  LEVEL: %d SOURCE: %d MESSAGE: %s\n\n", ((logger_pckt *)log)->time_stamp,((logger_pckt *)log)->log_level, ((logger_pckt *)log)->log_source,((logger_pckt *)log)->log_msg);
        		fflush(pfd);
	        }

	}
	
}