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
//*****************************************************************************
//
// This task toggles the user selected LED at a user selected frequency. User
// can make the selections by pressing the left and right buttons.
//
//*****************************************************************************
static void
Task1(void *pvParameters)
{
    while(1)
    {
        // Read the next message, if available on queue.
        //

        if(xQueueReceive(g_pTASK1Queue, &i8Message1, 0) == pdPASS)
        {
            xTaskNotify(handle3,TOGGLE_LED,eSetBits);
//            UARTprintf("T3 notified from T1\n");
        }
    }
}

static void
Task2(void *pvParameters)
{
    TickType_t ticks;
    //
    // Loop forever.
    //
    while(1)
    {
        // Read the next message, if available on queue.
        //
        ticks=xTaskGetTickCount();
        if(xQueueReceive(g_pTASK2Queue, &i8Message2, 0) == pdPASS)
        {
            xQueueSendFromISR(g_pTASK3Queue,&ticks,0);
            xTaskNotify(handle3,LOG_STRING,eSetBits);
//            UARTprintf("T3 notified from T2\n");

        }
    }
}

static void
Task3(void *pvParameters)
{
uint32_t tickcount;
uint32_t receivesig;
    //
    // Loop forever.
    //
    while(1)
    {
        // Read the next message, if available on queue.
        //
        xTaskNotifyWait(0xFFFFFFFF,receivesig,&receivesig,portMAX_DELAY);

          if(receivesig&TOGGLE_LED)
          {
          count2++;
          if(count2%2==0)
           {
              // Turn on the LED.
             //
             GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_1, GPIO_PIN_1);
           }
          else
          {
               // Turn off the LED.
               //
              GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_1, 0x0);
           }
          }
          else if (receivesig&LOG_STRING)
          {
              xQueueReceive(g_pTASK3Queue,&tickcount,portMAX_DELAY);
              UARTprintf("TASK 2 TICK is %d\n",tickcount);
          }
    }
}

void Timer0IntHandler(TimerHandle_t xTimer)
{
      /* Increment the count, then test to see if the timer has expired
      ulMaxExpiryCountBeforeStopping yet. */
//    UARTprintf("TIMERRRR INTER\n");
      count++;
      if(count%2==0){
//           UARTprintf("INTR T2 : %d\n\r",count);
           xQueueSendFromISR(g_pTASK2Queue,&i8Message1,0);
         }

//      UARTprintf("INTR T1 : %d\n\r",count);
    xQueueSendFromISR(g_pTASK1Queue,&i8Message2,0);
}

//*****************************************************************************
//
// Initializes the LED task.
//
//*****************************************************************************
uint32_t
Task1Init(void)
{
    UARTprintf("Initializaing T1 \n\r");
        //
        // Create a queue for sending messages to the LED task.
        //
        g_pTASK1Queue = xQueueCreate(LED_QUEUE_SIZE, LED_ITEM_SIZE);
    if(pdTRUE!=xTaskCreate(Task1,"Task1",32,NULL,2,&handle1))
        {
        while(1);

        }

    //
    // Success.
    //
    return(0);
}
uint32_t
Task2Init(void)
{
    UARTprintf("Initializaing T2 \n\r");
        //
        // Create a queue for sending messages to the LED task.
        //
        g_pTASK2Queue = xQueueCreate(LED_QUEUE_SIZE, LED_ITEM_SIZE);
    if(pdTRUE!=xTaskCreate(Task2,"Task2",32,NULL,2,&handle2))
        {
        while(1);
        }

    //
    // Success.
    //
    return(0);
}

uint32_t
Task3Init(void)
{
    UARTprintf("Initializaing T3 \n\r");
        //
        // Create a queue for sending messages to the LED task.
        //
        g_pTASK3Queue = xQueueCreate(LED_QUEUE_SIZE, LED_ITEM_SIZE);
    if(pdTRUE!=xTaskCreate(Task3,"Task3",32,NULL,3,&handle3))
        {
        while(1);
        }

    //
    // Success.
    //
    return(0);
}


//*****************************************************************************
//
// Configure the UART and its pins.  This must be called before UARTprintf().
//
//*****************************************************************************
void ConfigureUART(void)
{
    //
     // Enable the GPIO port that is used for the on-board LED.
     //
     ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPION);

     //
     // Enable the GPIO pins for the LED (PN0).
     //
     ROM_GPIOPinTypeGPIOOutput(GPIO_PORTN_BASE, GPIO_PIN_0);
     ROM_GPIOPinTypeGPIOOutput(GPIO_PORTN_BASE, GPIO_PIN_1);

     //
     // Enable the peripherals used by this example.
     //
     ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
     ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
     //
        // Set GPIO A0 and A1 as UART pins.
        //
        GPIOPinConfigure(GPIO_PA0_U0RX);
        GPIOPinConfigure(GPIO_PA1_U0TX);
        ROM_GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

        UARTStdioConfig(0,115200,g_ui32SysClock);
}
int count=0;

//*****************************************************************************
//
// Initialize FreeRTOS and start the initial set of tasks.
//
//*****************************************************************************

int main(void)
{

   g_ui32SysClock = MAP_SysCtlClockFreqSet((SYSCTL_XTAL_25MHZ |
                                            SYSCTL_OSC_MAIN |
                                            SYSCTL_USE_PLL |
                                            SYSCTL_CFG_VCO_480), 120000000);
        //
    // Initialize the UART and configure it for 115,200, 8-N-1 operation.
    //
    ConfigureUART();

    if (Task1Init() != 0)     //0 means success
    {

        while (1)
        {

        }
    }

    if (Task2Init() != 0)     //0 means success
        {

            while (1)
            {

            }
        }

    if (Task3Init() != 0)     //0 means success
            {

                while (1)
                {

                }
            }


    //---------timers

    MyTimer = xTimerCreate
                        ( /* Just a text name, not used by the RTOS
                         kernel. */
                         "Timer",
                         /* The timer period in ticks, must be
                         greater than 0. */
                         TIMER_TIME,
                         /* The timers will auto-reload themselves
                         when they expire. */
                         pdTRUE,
                         /* The ID is used to store a count of the
                         number of times the timer has expired, which
                         is initialised to 0. */
                         ( void * ) 0,
                         /* Each timer calls the same callback when
                         it expires. */
                         Timer0IntHandler
                        );

             if( MyTimer == NULL )
             {
                 /* The timer was not created. */
                 UARTprintf("TIMER ERROR\n");
             }
             else
             {
                 /* Start the timer.  No block time is specified, and
                 even if one was it would be ignored because the RTOS
                 scheduler has not yet been started. */
                 if( xTimerStart( MyTimer, 0 ) != pdPASS )
                 {
                     UARTprintf("The timer could not be set into the Active state\r\n");
                 }
             }

    //---------timers

    //
    // Start the scheduler.  This should not return.
    //
    vTaskStartScheduler();

    //
    // In case the scheduler returns for some reason, print an error and loop
    // forever.
    //

    while (1)
    {
    }
}
