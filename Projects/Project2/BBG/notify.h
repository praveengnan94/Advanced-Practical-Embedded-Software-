/***************************************************************
* AUTHOR  : Praveen Gnanasekaran
* DATE    : 04/28/2018
* DESCRITPTION  : notify.h
                  
* SOURCE FILES  : notify.c
****************************************************************/

#include <signal.h>

#define FREQ_NSEC (1000000000)

#define MAGNETO_SIGNAL_OPT    (SIGRTMAX)
#define MAGNETO_SIG_HEARTBEAT (SIGRTMAX-1)
#define MAGNETO_SIG (SIGRTMAX-2)

sig_atomic_t magneto_close_flag;

int magneto_init_timer();
void magneto_timer_sig_handler(int sig);
