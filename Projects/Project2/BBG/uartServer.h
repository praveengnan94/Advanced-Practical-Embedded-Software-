#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>   // using the termios.h library
#include "includes.h"

typedef struct{
	// uint32_t clientinfo;
	// uint32_t serverinfo;
	// float uv_payload;
	// float pr_payload;
	char buffer[30];
}uartstructre;

void uartinit();
int uartWrite(uartstructre *uartstruct);
int uartRead(uartstructre *uartstruct);

int uartfile;
struct termios uartoptions;               //The termios structure is vital
