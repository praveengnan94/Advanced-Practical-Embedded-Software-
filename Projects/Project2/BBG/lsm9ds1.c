/***************************************************************
* AUTHOR  : Praveen Gnanaseakran
* DATE    : 03/08/2018
* DESCRITPTION  : TEMPERATURE FUNCTIONS
                  
* HEADER FILES  : tmp102.h
****************************************************************/

#include "lsm9ds1.h"

extern int i2c_glb_pass;

int Magneto_sensor_init() {
  int magn;
  magn = i2cInit("/dev/i2c-2", magn, MAGNETO_ADDR);
  return magn;
}

void magn_CONFIG_write(int file_handler, char *buffer) {
  if(i2cWrite(file_handler, buffer, 2)<0)
  	{
  		i2c_glb_pass=-1;
  		printf("CANNOT OPEN I2C\n");
  	}
  	else
  	i2c_glb_pass=1;
}

void magn_CONFIG_read(int file_handler, char *buffer) {
  if(i2cWrite(file_handler, buffer, 1)<0)
  {
  	i2c_glb_pass=-1;
  	printf("CANNOT OPEN I2C\n");
  }
  else
  	i2c_glb_pass=1;
  if(i2cRead(file_handler, buffer, 1)<0)
  {
  	i2c_glb_pass=-1;
  	printf("CANNOT OPEN I2C\n");
  }
  else
  	i2c_glb_pass=1;
}

uint8_t magn_VALUE_read(int file_handler, char *buffer){
  if(i2cWrite(file_handler, buffer, 1)<0)
  {
  	i2c_glb_pass=-1;
  	printf("CANNOT OPEN I2C\n");
  }
  else
  	i2c_glb_pass=1;
  if(i2cRead(file_handler, buffer, 1)<0)
  {
  	i2c_glb_pass=-1;
  	printf("CANNOT OPEN I2C\n");
  }
  else
  	i2c_glb_pass=1;
  	return buffer[0];
}