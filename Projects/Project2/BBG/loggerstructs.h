/***************************************************************
* AUTHOR  : Praveen Gnanaseakran
* DATE    : 03/08/2018
* DESCRITPTION  : loggerstructs
                  
****************************************************************/
typedef struct{
char time_stamp[32];
char log_msg[BUFFER_SIZE -100];
uint8_t log_level;
}logger_pckt;

