/***************************************************************
* AUTHOR  : Praveen Gnanaseakran
* DATE    : 03/08/2018
* DESCRITPTION  : includes files
                  
****************************************************************/

#ifndef includes_H
#define includes_H

#include <stdint.h>
#define PORT 8080
#define DEFAULT_FILE_NAME ("logfile.txt")
char* fileid;
#define BUFFER_SIZE 4096

#define LED_ON (system("echo 1 > /sys/class/leds/beaglebone:green:usr0/brightness"))
#define LED_OFF (system("echo 0 > /sys/class/leds/beaglebone:green:usr0/brightness"))

#define LED_ON2 (system("echo 1 > /sys/class/leds/beaglebone:green:usr1/brightness"))
#define LED_OFF2 (system("echo 0 > /sys/class/leds/beaglebone:green:usr1/brightness"))

#define READY_LED 		(system("echo none >/sys/class/leds/beaglebone:green:usr1/trigger"))
#define READY_LED2 		(system("echo none >/sys/class/leds/beaglebone:green:usr2/trigger"))
#endif

pthread_mutex_t lock_i2c;

// typedef enum{
// init,
// error,
// notification
// }msg_type;

// typedef struct{
// char msg[BUFFER_SIZE-sizeof(msg_type)];
// msg_type type;
// }alert_message;

// typedef enum {
//   temperatue_Task,
//   light_Task,
//   RemoteRequestSocket_Task,
//   error_handler
// }task_type;

// typedef struct{
// char time_stamp[32];
// task_type log_source;
// char log_msg[BUFFER_SIZE -100];
// uint8_t log_level;
// }logger_pckt;

// typedef enum{
// temperature,
// light
// }sensor_type;

// //request structure
//   typedef struct {
//   sensor_type sensor;
//   temp_unit tunit;//if sensor is temperature
//   light_unit lunit;
// }sock_req;

