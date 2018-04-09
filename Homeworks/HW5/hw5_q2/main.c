/***************************************************************
* AUTHOR  : Praveen Gnanasekaran
* DATE    : 04/06/2018
* DESCRIPTION  : DriverLib
* HEADER FILES  : main.h
****************************************************************/

#include "main.h"

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

              //Poll and blink LED and print UART messages
              while(1)
              {
                  count++;
                  ROM_SysCtlDelay(TIME_VALUE); //Calculations for delay in the macro
                  GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_0, GPIO_PIN_0);
                  UARTprintf("Project for:PRAVEEN_GNANASEKARAN 04/08/2018 LED COUNT : %d\n",count);
                  ROM_SysCtlDelay(TIME_VALUE);
                  GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_0, 0x0);
              }
	return 0;
}
