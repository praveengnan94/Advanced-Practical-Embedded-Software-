#include "MagnetoTask.h"

void *MagnetoTask(void *pthread_inf) {
  
  uint8_t initialize = 1;
  char initialize_msg[8][4096];

  int magn = Magneto_sensor_init();
  char magn_data[2], data_cel_str[BUFFER_SIZE - 200];
  float data_cel;

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


  if (magn == -1) 
  {
    initialize = 0;
    sprintf(&(initialize_msg[6][0]), "Magn init Error\n");
  } 
  else 
  {
    sprintf(&(initialize_msg[6][0]), "Magn init Success\n");
  }

  char buffer[2];
  buffer[0]=MAG_CTRL_REG1_ADDR;
  buffer[1]=MAG_CTRL_REG1_CONFIG;
  magn_CONFIG_write(magn,buffer);
  magn_CONFIG_read(magn,buffer);

  buffer[0]=MAG_CTRL_REG2_ADDR;
  buffer[1]=MAG_CTRL_REG2_CONFIG;
  magn_CONFIG_write(magn,buffer);
  magn_CONFIG_read(magn,buffer);

  buffer[0]=MAG_CTRL_REG3_ADDR;
  buffer[1]=MAG_CTRL_REG3_CONFIG;
  magn_CONFIG_write(magn,buffer);
  magn_CONFIG_read(magn,buffer);

  buffer[0]=MAG_CTRL_REG4_ADDR;
  buffer[1]=MAG_CTRL_REG4_CONFIG;
  magn_CONFIG_write(magn,buffer);
  magn_CONFIG_read(magn,buffer);

  buffer[0]=MAG_CTRL_REG5_ADDR;
  buffer[1]=MAG_CTRL_REG5_CONFIG;
  magn_CONFIG_write(magn,buffer);
  magn_CONFIG_read(magn,buffer);

while(1)
{
  uint8_t* temp;
  uint8_t mxl,myl,mzl;
  uint8_t mxh,myh,mzh;
  uint8_t mx,my,mz;

  buffer[0]=OUT_X_L_M;
  mxl=magn_VALUE_read(magn,buffer);

  buffer[0]=OUT_X_H_M;
  mxh=magn_VALUE_read(magn,buffer);
  mx=mxh<<8|mxl;
  // printf("%d,",mx);

  buffer[0]=OUT_Y_L_M;
  myl=magn_VALUE_read(magn,buffer);

  buffer[0]=OUT_Y_H_M;
  myh=magn_VALUE_read(magn,buffer);
  my=myh<<8|myl;
  // printf(" %d,",my);

  buffer[0]=OUT_Z_L_M;
  mzl=magn_VALUE_read(magn,buffer);

  buffer[0]=OUT_Z_H_M;
  mzh=magn_VALUE_read(magn,buffer);
  mz=mzh<<8|mzl;
  // printf(" %d\n",mz);
	
	

	threadTaskAttr *pthread_info = (threadTaskAttr *)pthread_inf;
   while (magneto_flag_glb == 0) 
    {
      pthread_cond_wait(&cond_var_magneto, &lock_magneto);
    }

    magneto_flag_glb = 0;
    pthread_kill(pthread_info->main, MAGNETO_SIG_HEARTBEAT);

    len_bytes = mq_send(msg_queue, "MAGNETOMETER DATA", strlen("MAGNETOMETER DATA"), (unsigned int )MESSAGE_PRIORITY);
		        if(len_bytes < 0) 
			{
				printf("ERROR: child_to_parent message sending fail\n"); 
				return 0;
			}
		        else
		        {} 
				// printf("SENT: message from child to parent\n");


}
 //  uint8_t mx,my,mz;
  
	// mx = (temp[1] << 8) | temp[0]; // Store x-axis values into mx
	// my = (temp[3] << 8) | temp[2]; // Store y-axis values into my
	// mz = (temp[5] << 8) | temp[4]; // Store z-axis values into mz
	// printf("%x %x %x\n",mx,my,mz);

}