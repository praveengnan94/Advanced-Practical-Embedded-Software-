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
//
// System clock rate in Hz.
//
//****************************************************************************
uint32_t g_ui32SysClock;


//*****************************************************************************
//
// Send a string to the UART.
//
//*****************************************************************************
void
UARTSend(const uint8_t *pui8Buffer, uint32_t ui32Count)
{
    //
    // Loop while there are more characters to send.
    //
    while(ui32Count--)
    {
        //
        // Write the next character to the UART.
        //
        ROM_UARTCharPutNonBlocking(UART0_BASE, *pui8Buffer++);
    }
}

/**
 * main.c
 */
int main(void)
{
    //
        // Set the clocking to run directly from the crystal at 120MHz.
        //
        g_ui32SysClock = MAP_SysCtlClockFreqSet((SYSCTL_XTAL_25MHZ |
                                                 SYSCTL_OSC_MAIN |
                                                 SYSCTL_USE_PLL |
                                                 SYSCTL_CFG_VCO_480), 120000000);
        //
           // Enable the GPIO port that is used for the on-board LED.
           //
           ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPION);

           //
           // Enable the GPIO pins for the LED (PN0).
           //
           ROM_GPIOPinTypeGPIOOutput(GPIO_PORTN_BASE, GPIO_PIN_0);

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
              SysCtlClockSet(SYSCTL_SYSDIV_2_5|SYSCTL_USE_PLL|SYSCTL_OSC_MAIN);

              while(1)
              {
                  ROM_SysCtlDelay(TIME_VALUE);
                  GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_0, GPIO_PIN_0);
                  ROM_SysCtlDelay(TIME_VALUE);
                  GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_0, 0x0);
              }
	return 0;
}
