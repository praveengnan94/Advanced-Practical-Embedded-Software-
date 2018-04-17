/***************************************************************
* AUTHOR  : Praveen Gnanaseakran
* DATE    : 03/08/2018
* DESCRITPTION  : NOTIFY FILES
                  
* SOURCE FILES  : notify.c
****************************************************************/

#include <signal.h>

#define FREQ_NSEC (1000000000)

#define ACCEL_SIGNAL_OPT     (SIGRTMAX)
#define LIGHT_SIGNAL_OPT    (SIGRTMAX-1)

#define LIGHT_SIG_HEARTBEAT (SIGRTMAX-2)
#define ACCEL_SIG_HEARTBEAT  (SIGRTMAX-3)
#define LOGGER_SIG_HEARTBEAT  (SIGRTMAX-4)

#define TEMPSIGNAL_PACKET (SIGRTMAX-5)
#define LIGHTSIGNAL_PACKET (SIGRTMAX-6)

#define LOGGER_SIG (SIGRTMAX-7)

#define SOCKET_SIG_HEARTBEAT  (SIGRTMAX-8)

void SIGNAL_INTERRUPT_HANDL(int sig);

sig_atomic_t accel_close_flag;

void SIGNAL_INTERRUPT_HANDL(int sig);

int accel_init_timer();

int timer_init_light();

void accel_sig_handler(int sig);