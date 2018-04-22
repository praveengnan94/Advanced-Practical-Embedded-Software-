/***************************************************************
* AUTHOR  : Praveen Gnanaseakran
* DATE    : 03/08/2018
* DESCRITPTION  : NOTIFY FILES
                  
* SOURCE FILES  : notify.c
****************************************************************/

#include <signal.h>

#define FREQ_NSEC (1000000000)

#define ACCEL_SIGNAL_OPT     (SIGRTMAX)
#define LOGGER_SIGNAL_OPT    (SIGRTMAX-1)
#define MAGNETO_SIGNAL_OPT    (SIGRTMAX-2)
#define COMM_SIGNAL_OPT    (SIGRTMAX-3)

#define MAGNETO_SIG_HEARTBEAT (SIGRTMAX-4)
#define ACCEL_SIG_HEARTBEAT  (SIGRTMAX-5)
#define LOGGER_SIG_HEARTBEAT  (SIGRTMAX-6)
#define COMM_SIG_HEARTBEAT  (SIGRTMAX-7)

#define LOGGER_SIG (SIGRTMAX-8)
#define ACCEL_SIG (SIGRTMAX-9)
#define MAGNETO_SIG (SIGRTMAX-10)
#define COMM_SIG (SIGRTMAX-11)

sig_atomic_t accel_close_flag;
sig_atomic_t magneto_close_flag;
sig_atomic_t logger_close_flag;
sig_atomic_t comm_close_flag;

void SIGNAL_INTERRUPT_HANDL(int sig);

int init_timer();
void timer_sig_handler(int sig);
