#include "LoggerTask.h"

void *LoggerTask(void *pthread_inf) {
	int ret;
	

	threadTaskAttr *pthread_info = (threadTaskAttr *)pthread_inf;
	 
	while(1)
	{
	   while (logger_flag_glb == 0) 
	    {
	      pthread_cond_wait(&cond_var_logger, &lock_logger);
	    }

	    logger_flag_glb = 0;
	    pthread_kill(pthread_info->main, LOGGER_SIG_HEARTBEAT);

	}
	
}