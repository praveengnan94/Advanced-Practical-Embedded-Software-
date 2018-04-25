#include "AccelTask.h"
void *AccelTask(void *pthread_inf) {
	int ret;
	

	threadTaskAttr *pthread_info = (threadTaskAttr *)pthread_inf;

	int priority, len_bytes;
        struct mq_attr attr = {
								.mq_maxmsg = 16, 
                                .mq_msgsize = BUFFER_SIZE, 
                                .mq_flags = 0
				};

    mqd_t msg_queue;

     msg_queue = mq_open(ACCEL_MSGQ_IPC, O_RDWR | O_CREAT, S_IRWXU, &attr);

	        if(msg_queue < 0) 
			{ 
				perror("ERROR:\n"); 
				return 0;
			}

	 
	while(1)
	{
	   while (accel_flag_glb == 0) 
	    {
	      pthread_cond_wait(&cond_var_accel, &lock_accel);
	    }

	    accel_flag_glb = 0;
	    pthread_kill(pthread_info->main, ACCEL_SIG_HEARTBEAT);

	     len_bytes = mq_send(msg_queue, "ACCELEROMETER DATA", strlen("ACCELEROMETER DATA"), (unsigned int )MESSAGE_PRIORITY);
		        if(len_bytes < 0) 
			{
				printf("ERROR: child_to_parent message sending fail\n"); 
				return 0;
			}
		        else {}
				// printf("SENT: message from child to parent\n");

	}
}