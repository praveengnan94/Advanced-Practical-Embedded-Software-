/***************************************************************
* AUTHOR  : Praveen Gnanasekaran
* DATE    : 04/06/2018
* DESCRIPTION  : DriverLib
* SOURCE FILES  : main.c
****************************************************************/

/*
 * main.h
 *
 *  Created on: Apr 8, 2018
 *      Author: PGnanasekaran
 */

#ifndef MAIN_H_
#define MAIN_H_

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "driverlib/debug.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/pin_map.h"
#include "driverlib/rom.h"
#include "driverlib/rom_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "utils/uartstdio.h"

#define TIME_VALUE (SysCtlClockGet()/3)*8.33 // 16.66- 1Hz for 120MHz clock. So 8.33 for 2Hz

uint32_t count;
//
// System clock rate in Hz.
//
//****************************************************************************
uint32_t g_ui32SysClock;

#endif /* MAIN_H_ */
