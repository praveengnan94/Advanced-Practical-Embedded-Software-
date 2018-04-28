/***************************************************************
* AUTHOR  : Praveen Gnanaseakran
* DATE    : 03/08/2018
* DESCRITPTION  : NOTIFY FILES
                  
* SOURCE FILES  : notify.c
****************************************************************/

#include <signal.h>

#define FREQ_NSEC (1000000000)

#define MAGNETO_SIGNAL_OPT    (SIGRTMAX)
#define MAGNETO_SIG_HEARTBEAT (SIGRTMAX-4)
#define MAGNETO_SIG (SIGRTMAX-10)

sig_atomic_t magneto_close_flag;

int magneto_init_timer();
void magneto_timer_sig_handler(int sig);