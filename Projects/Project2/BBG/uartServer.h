/***************************************************************
* AUTHOR  : Praveen Gnanasekaran
* DATE    : 04/28/2018
* DESCRITPTION  : uartServer.h
                  
* SOURCE FILES  : uartServer.c
****************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>   // using the termios.h library
#include "includes.h"

typedef struct{
	uint32_t clientid;
	uint32_t clientinfo;
	float uv_payload;
	float pr_payload;
}uartstructre;

void uartinit();
int uartWrite(uartstructre *uartstruct);
int uartRead(uartstructre *uartstruct);

int uartfile;
struct termios uartoptions;               //The termios structure is vital
