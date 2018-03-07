/***************************************************************
* AUTHOR  : Praveen Gnanasekaran
* DATE    : 03/06/2018
* DESCRIPTION  : This program explores various IPC mechanisms to communicate in Linux
* HEADER FILES  : q2.h
****************************************************************/
#include "q2sock.c"
#include "q2pipes.c"
#include "q2msgq.c"
#include "q2sharedmem.c"


int main(int argc, char *argv[])
{

    if(strcmp(argv[1],"pipes")==0)
        pipes();
    else if(strcmp(argv[1],"sock")==0)
        sock();
    else if(strcmp(argv[1],"msgq")==0)
        msgq();
    else if(strcmp(argv[1],"mem")==0)
        sharedmem();
    else
    {
        printf("Improper usage\n");
        exit(1);
    }    
    
    return 0;
}