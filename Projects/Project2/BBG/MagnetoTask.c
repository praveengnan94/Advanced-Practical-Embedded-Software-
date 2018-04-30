/***************************************************************
* AUTHOR  : Praveen Gnanasekaran
* DATE    : 04/28/2018
* DESCRITPTION  : MagnetoTask.c
                  
* HEADER FILES  : MagnetoTask.h
****************************************************************/
#include "MagnetoTask.h"

extern int magneto_heartbeat_flag;
extern uint8_t magneto_exit_flag;
void *MagnetoTask(void *pthread_inf) {
  
  uint8_t initialize = 1;
  char initialize_msg[8][4096];


  char magn_data[2], data_cel_str[BUFFER_SIZE - 200],accel_data[2];
  float data_cel;

  int priority, len_bytes,ret;
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

 int magn = Magneto_sensor_init();
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


  ret = magneto_init_timer(); 

  if (ret == -1) 
  {
    initialize = 0;
    sprintf(&(initialize_msg[1][0]), "Failure MAGNETO init_timer \n");
  } 
  else 
  {
    sprintf(&(initialize_msg[1][0]), "Success MAGNETO init_timer \n");
  }
  uint8_t* temp;
  uint8_t mxl,myl,mzl;
  uint8_t mxh,myh,mzh;
  uint16_t mx,my,mz;

  uint8_t axl,ayl,azl;
  uint8_t axh,ayh,azh;
  uint16_t ax,ay,az;

  float offx,offy,offz;

  float dir;

  while(magneto_exit_flag==0)
  {

  buffer[0]=STATUS_REG_M;
  mxl=magn_VALUE_read(magn,buffer);
  while(!(mxl&7))
  {
    buffer[0]=STATUS_REG_M;
    mxl=magn_VALUE_read(magn,buffer);
    
  }

  buffer[0]=OUT_X_L_M;
  mxl=magn_VALUE_read(magn,buffer);

  buffer[0]=OUT_Y_L_M;
  myl=magn_VALUE_read(magn,buffer);

  buffer[0]=OUT_Z_L_M;
  mzl=magn_VALUE_read(magn,buffer);


    logger_pckt magneto_log = {.log_level = 1};

    sprintf(data_cel_str, "X: %d [G] Y: %d [G] Z: %d [G]", mxl,myl,mzl);
    strcpy(magneto_log.log_msg, data_cel_str);

    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    strcpy(magneto_log.time_stamp, asctime(tm));
    clock_gettime(CLOCK_MONOTONIC, &current);
    expire.tv_sec = current.tv_sec + 2;
    expire.tv_nsec = current.tv_nsec;

	threadTaskAttr *pthread_info = (threadTaskAttr *)pthread_inf;
   while (magneto_flag_glb == 0) 
    {

    }
    magneto_flag_glb = 0;
    magneto_heartbeat_flag=1;

    len_bytes = mq_send(msg_queue,(const char *)&magneto_log,sizeof(logger_pckt), (unsigned int )MESSAGE_PRIORITY);
		        if(len_bytes < 0) 
			{
				printf("ERROR: child_to_parent message sending fail\n"); 
				return 0;
			}
		        else
		        {
            } 
  }

}