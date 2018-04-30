#include "AccelTask.h"

extern int accel_heartbeat_flag;
extern uint8_t accel_exit_flag;

void *AccelTask(void *pthread_inf) {
  
  uint8_t initialize = 1;
  char initialize_msg[8][4096];


  char  data_cel_str[BUFFER_SIZE - 200],accel_data[2];
  float data_cel;

  int priority, len_bytes,ret;
        struct mq_attr attr = {
								                .mq_maxmsg = 16, 
                                .mq_msgsize = BUFFER_SIZE, 
                                .mq_flags = 0
				};

    mqd_t msg_queue2;


      msg_queue2 = mq_open(MAGNETO_MSGQ_IPC, O_RDWR | O_CREAT, S_IRWXU, &attr);

          if(msg_queue2 < 0) 
      { 
        perror("ERROR:\n"); 
        return 0;
      }

  int accel = Accel_sensor_init();
  if (accel == -1) 
  {
    initialize = 0;
    sprintf(&(initialize_msg[6][0]), "Accel init Error\n");
  } 
  else 
  {
    sprintf(&(initialize_msg[6][0]), "Accel init Success\n");
  }
  
  char buffer[2];
  buffer[0]=ACCEL_CTRL_REG5_XL_ADDR;
  buffer[1]=ACCEL_CTRL_REG5_XL_CONFIG;
  magn_CONFIG_write(accel,buffer);
  magn_CONFIG_read(accel,buffer);

  buffer[0]=ACCEL_CTRL_REG6_XL_ADDR;
  buffer[1]=ACCEL_CTRL_REG6_XL_CONFIG;
  magn_CONFIG_write(accel,buffer);
  magn_CONFIG_read(accel,buffer);

  buffer[0]=ACCEL_CTRL_REG7_XL_ADDR;
  buffer[1]=ACCEL_CTRL_REG7_XL_CONFIG;
  magn_CONFIG_write(accel,buffer);
  magn_CONFIG_read(accel,buffer);


  uint8_t* temp;
  uint8_t axl,ayl,azl;
  uint8_t axh,ayh,azh;
  uint16_t ax,ay,az;

  float dir;

  while(magneto_exit_flag==0)
  {

  buffer[0]=OUT_Z_L_A;
  azl=magn_VALUE_read(accel,buffer);

  buffer[0]=STATUS_REG_A;
  axl=magn_VALUE_read(accel,buffer);
  while(!(axl&1))
  {
    buffer[0]=STATUS_REG_A;
    axl=magn_VALUE_read(accel,buffer);
    
  }

  buffer[0]=OUT_X_L_A;
  axl=magn_VALUE_read(accel,buffer);
  
  buffer[0]=OUT_Y_L_A;
  ayl=magn_VALUE_read(accel,buffer);
  
  buffer[0]=OUT_Z_L_A;
  azl=magn_VALUE_read(accel,buffer);


    logger_pckt accel_log = {.log_level = 1};
    

    sprintf(data_cel_str, "X: %d [G] Y: %d [G] Z: %d [G]", axl,ayl,azl);
    strcpy(accel_log.log_msg, data_cel_str);


    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    strcpy(accel_log.time_stamp, asctime(tm));
    clock_gettime(CLOCK_MONOTONIC, &current);
    expire.tv_sec = current.tv_sec + 2;
    expire.tv_nsec = current.tv_nsec;



	threadTaskAttr *pthread_info = (threadTaskAttr *)pthread_inf;
   while (accel_flag_glb == 0) 
    {

    }
    accel_flag_glb = 0;
    accel_heartbeat_flag=1;

    len_bytes = mq_send(msg_queue2,(const char *)&accel_log,sizeof(logger_pckt), (unsigned int )MESSAGE_PRIORITY);
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