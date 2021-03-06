/***************************************************************
* AUTHOR  : Praveen Gnanasekaran
* DATE    : 04/28/2018
* DESCRITPTION  : msgque.h
                  
****************************************************************/
#include <mqueue.h>

#define BUFFER_SIZE 4096
#define MESSAGEQ_SIZE 10
#define MESSAGE_PRIORITY  30
#define INIT_MESSAGE_PRIORITY 25
#define ERROR_MESSAGE_PRIORITY 20

#define LOGGER_MSGQ_IPC   "/logger_MSG"
#define ACCEL_MSGQ_IPC   "/ACCEL_MSGQ_IPC"
#define MAGNETO_MSGQ_IPC   "/MAGNETO_MSGQ_IPC"
#define COMM_MSGQ_IPC   "/COMM_MSGQ_IPC"


