/***************************************************************
* AUTHOR  : Praveen Gnanaseakran
* DATE    : 03/08/2018
* DESCRITPTION  : TEMPERATURE FUNCTIONS
                  
* HEADER FILES  : tmp102.h
****************************************************************/

#include "lsm9ds1.h"

int Magneto_sensor_init() {
  int magn;
  magn = i2cInit("/dev/i2c-2", magn, MAGNETO_ADDR);
  return magn;
}

void magn_CONFIG_write(int file_handler, char *buffer) {
  i2cWrite(file_handler, buffer, 2);
}

void magn_CONFIG_read(int file_handler, char *buffer) {
  i2cWrite(file_handler, buffer, 1);
  i2cRead(file_handler, buffer, 1);
}

uint8_t magn_VALUE_read(int file_handler, char *buffer){
	i2cWrite(file_handler, buffer, 1);
  	i2cRead(file_handler, buffer, 1);	
  	return buffer[0];
}