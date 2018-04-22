#include "AccelTask.h"

void *AccelTask(void *pthread_inf) {
	int ret;
	

	threadTaskAttr *pthread_info = (threadTaskAttr *)pthread_inf;
	 
	while(1)
	{
	   while (accel_flag_glb == 0) 
	    {
	      pthread_cond_wait(&cond_var_accel, &lock_accel);
	    }

	    accel_flag_glb = 0;
	    pthread_kill(pthread_info->main, ACCEL_SIG_HEARTBEAT);

	}
}