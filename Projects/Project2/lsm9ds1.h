/***************************************************************
* AUTHOR  : Praveen Gnanaseakran
* DATE    : 03/08/2018
* DESCRITPTION  : TEMPERATURE FUNCTIONS
                  
* SOURCE FILES  : tmp102.c
****************************************************************/

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <err.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <linux/types.h>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include "i2c_wrap.h"
#include "includes.h"


#define ACCEL_ADDR (0x6A)
#define MAGNETO_ADDR (0x1C)

#define MAG_CTRL_REG1_ADDR 0x20
#define MAG_CTRL_REG2_ADDR 0x21
#define MAG_CTRL_REG3_ADDR 0x22
#define MAG_CTRL_REG4_ADDR 0x23
#define MAG_CTRL_REG5_ADDR 0x24

#define MAG_CTRL_REG1_CONFIG 0xA0
#define MAG_CTRL_REG2_CONFIG 0x00
#define MAG_CTRL_REG3_CONFIG 0x00
#define MAG_CTRL_REG4_CONFIG 0x00
#define MAG_CTRL_REG5_CONFIG 0x00

#define OUT_X_L_M 0x28
#define OUT_X_H_M 0x29
#define OUT_Y_L_M 0x2A
#define OUT_Y_H_M 0x2B
#define OUT_Z_L_M 0x2C
#define OUT_Z_H_M 0x2D

int Magneto_sensor_init();
void magn_CONFIG_write(int file_handler, char *buffer);
void magn_CONFIG_read(int file_handler, char *buffer);

uint8_t magn_VALUE_read(int file_handler, char *buffer);