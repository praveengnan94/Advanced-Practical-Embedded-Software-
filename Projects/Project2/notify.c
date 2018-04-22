#include <stdio.h>
#include <errno.h>
#include <pthread.h>
#include <signal.h>
#include <unistd.h>
#include "notify.h"
#include <errno.h>
#include <string.h>
#include "threads.h"

int accel_init_timer(){
    int ret;

    struct sigaction sig_act ={.sa_flags = SA_RESTART,.sa_handler = accel_sig_handler};
    printf("ACCEL TIMER\n");
    ret = sigaction(ACCEL_SIGNAL_OPT,&sig_act,NULL);
    if(ret == -1) 
        return -1;

    timer_t timerid;
    struct sigevent sig_ev ={.sigev_notify=SIGEV_SIGNAL,.sigev_signo = ACCEL_SIGNAL_OPT,.sigev_value.sival_ptr=&timerid};

    ret = timer_create(CLOCK_MONOTONIC,&sig_ev,&timerid);

    if(ret == -1) 
        return -1;

    struct itimerspec its={.it_value.tv_sec=3,.it_value.tv_nsec=0,.it_interval.tv_sec=FREQ_NSEC/1000000000,.it_interval.tv_nsec=FREQ_NSEC%1000000000};

    ret = timer_settime(timerid, 0, &its, NULL );

    if(ret == -1) 
        return -1;

    return 1;
}


void accel_sig_handler(int sig){
    printf("ACCEL SIG HANDLER\n");
    // pthread_mutex_lock(&lock_accel);
    accel_flag_glb = 1;
    pthread_cond_signal(&cond_var_accel);
    // pthread_mutex_unlock(&lock_accel);

}