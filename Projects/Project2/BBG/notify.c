#include <stdio.h>
#include <errno.h>
#include <pthread.h>
#include <signal.h>
#include <unistd.h>
#include "notify.h"
#include <errno.h>
#include <string.h>
#include "threads.h"

int magneto_init_timer(){
    int ret;

    struct sigaction sig_act ={.sa_flags = SA_RESTART,.sa_handler = magneto_timer_sig_handler};
    ret = sigaction(MAGNETO_SIGNAL_OPT,&sig_act,NULL);
    if(ret == -1) 
        return -1;

    timer_t timerid;
    struct sigevent sig_ev ={.sigev_notify=SIGEV_SIGNAL,.sigev_signo = MAGNETO_SIGNAL_OPT,.sigev_value.sival_ptr=&timerid};

    ret = timer_create(CLOCK_MONOTONIC,&sig_ev,&timerid);
    
    if(ret == -1) 
        return -1;

    struct itimerspec its={.it_value.tv_sec=3,.it_value.tv_nsec=0,.it_interval.tv_sec=FREQ_NSEC/1000000000,.it_interval.tv_nsec=FREQ_NSEC%1000000000};

    ret = timer_settime(timerid, 0, &its, NULL );

    if(ret == -1) 
        return -1;

    return 1;
}


void magneto_timer_sig_handler(int sig){
    magneto_flag_glb = 1;
}