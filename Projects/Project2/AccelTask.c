#include "AccelTask.h"

void *AccelTask(void *pthread_inf) {
	int ret;
	uint8_t initialize;
	char initialize_msg[8][4096];


	threadTaskAttr *pthread_info = (threadTaskAttr *)pthread_inf;
	 ret = accel_init_timer(); 

  if (ret == -1) 
  {
    initialize = 0;
    sprintf(&(initialize_msg[1][0]), "Failure Temptask accel_init_timer \n");
  } 
  else 
  {
    sprintf(&(initialize_msg[1][0]), "Success Temptask accel_init_timer \n");
  }

	while(1)
	{
	   while (accel_flag_glb == 0) 
	    {
	      pthread_cond_wait(&cond_var_accel, &lock_accel);
	    }

	    accel_flag_glb = 0;
	    pthread_kill(pthread_info->main, ACCEL_SIG_HEARTBEAT);

		printf("accel!!!!\n");
	}
}