/*
 * main.h
 *
 *  Created on: Apr 8, 2018
 *      Author: PGnanasekaran
 */

/***************************************************************
* AUTHOR  : Praveen Gnanasekaran
* DATE    : 04/06/2018
* DESCRIPTION  : EVENT DRIVEN UI
* SOURCE FILES  : main.c
****************************************************************/

#ifndef MAIN_H_
#define MAIN_H_

#include <FreeRTOS.h>
#include <task.h>
#include <timers.h>

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
#include "queue.h"
#include "timer.h"
#include "utilities/rom.h"

TimerHandle_t MyTimer;
#define TIMER_TIME pdMS_TO_TICKS(250)                //250ms
#define LED_ITEM_SIZE           sizeof(uint32_t)
#define LED_QUEUE_SIZE         40

#define TOGGLE_LED 0x01
#define LOG_STRING 0x02

long int count1,count2;
uint32_t g_ui32SysClock,i8Message1,i8Message2,i8Message;

xQueueHandle g_pTASK1Queue;
xQueueHandle g_pTASK2Queue;
xQueueHandle g_pTASK3Queue;

TaskHandle_t handle1,handle2,handle3;

int count;



#endif /* MAIN_H_ */
