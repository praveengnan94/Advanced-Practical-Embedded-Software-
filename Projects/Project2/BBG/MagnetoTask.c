#include "MagnetoTask.h"

void *MagnetoTask(void *pthread_inf) {
  
  uint8_t initialize = 1;
  char initialize_msg[8][4096];

  int magn = Magneto_sensor_init();
  char magn_data[2], data_cel_str[BUFFER_SIZE - 200];
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
    printf("FAIL\n");
    initialize = 0;
    sprintf(&(initialize_msg[1][0]), "Failure Temptask init_timer \n");
  } 
  else 
  {
    printf("SUCCESS\n");
    sprintf(&(initialize_msg[1][0]), "Success Temptask init_timer \n");
  }

  while(1)
  {
  // uint8_t* temp;
  // uint8_t mxl,myl,mzl;
  // uint8_t mxh,myh,mzh;
  // uint16_t mx,my,mz;
  // float offx,offy,offz;

  // float dir;

  // buffer[0]=STATUS_REG_M;
  // mxl=magn_VALUE_read(magn,buffer);
  // while(!(mxl&7))
  // {
  //   buffer[0]=STATUS_REG_M;
  //   mxl=magn_VALUE_read(magn,buffer);
    
  // }

  // buffer[0]=OUT_X_L_M;
  // mxl=magn_VALUE_read(magn,buffer);

  // buffer[0]=OUT_X_H_M;
  // mxh=magn_VALUE_read(magn,buffer);
  // mx=mxl<<8|mxh;
  // // mx=mxl*0.48828125;
  // // printf("%d,",mx);

  // buffer[0]=OUT_Y_L_M;
  // myl=magn_VALUE_read(magn,buffer);

  // buffer[0]=OUT_Y_H_M;
  // myh=magn_VALUE_read(magn,buffer);
  // my=myl<<8|myh;
  // // my=myl*0.48828125;
  // // printf("%d,",my);

  // buffer[0]=OUT_Z_L_M;
  // mzl=magn_VALUE_read(magn,buffer);

  // buffer[0]=OUT_Z_H_M;
  // mzh=magn_VALUE_read(magn,buffer);
  // mz=mzl<<8|mzh;
  // mz=mzl*0.48828125;
  // printf("%d,",mz);

  // buffer[0]=OFFSET_X_REG_L_M;
  // offx=magn_VALUE_read(magn,buffer);
  // printf("%f,",offx);

  // buffer[0]=OFFSET_Y_REG_L_M;
  // offy=magn_VALUE_read(magn,buffer);
  // printf("%f,",offy);

  // buffer[0]=OFFSET_Z_REG_L_M;
  // offz=magn_VALUE_read(magn,buffer);
  // printf("%f\n",offz);


/*Calculate the direction D by first checking to see if the X Gauss data is equal to 0 to prevent 
divide by 0 zero errors in the future calculations. If the X Gauss data is 0, check to see if the 
Y Gauss data is less than 0. If Y is less than 0 Gauss, the direction D is 90 degrees; 
if Y is greater than or equal to 0 Gauss, the direction D is 0 degrees.*/
 //  if(mx==0)
 //  {
 //    if(my<0)
 //      dir=90;
 //    else
 //      dir=0;
 //  }
 //  else
 //  {
 //    dir=atan(my/mx)*(180/3.14);
 //  }
	// // printf(",%f\n",dir);
	// if(dir>360)
 //    dir=dir-360;
 //  else if(dir<0)
 //    dir=dir+360;
  
/*If D is greater than 337.25 degrees or less than 22.5 degrees – North
If D is between 292.5 degrees and 337.25 degrees – North-West
If D is between 247.5 degrees and 292.5 degrees – West
If D is between 202.5 degrees and 247.5 degrees – South-West
If D is between 157.5 degrees and 202.5 degrees – South
If D is between 112.5 degrees and 157.5 degrees – South-East
If D is between 67.5 degrees and 112.5 degrees – East
If D is between 0 degrees and 67.5 degrees – North-East*/


  // if((dir>337.25)||(dir<337.25))
  //   printf("NORTH\n");
  // else if((dir>247.5)||(dir<247.5))
  //   printf("WEST\n");
  // else if((dir>157.5)||(dir<157.5))
  //   printf("SOUTH\n");
  // else if((dir>67.5)||(dir<67.5))
  //   printf("EAST\n");

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


  }
 //  uint8_t mx,my,mz;
  
	// mx = (temp[1] << 8) | temp[0]; // Store x-axis values into mx
	// my = (temp[3] << 8) | temp[2]; // Store y-axis values into my
	// mz = (temp[5] << 8) | temp[4]; // Store z-axis values into mz
	// printf("%x %x %x\n",mx,my,mz);

}