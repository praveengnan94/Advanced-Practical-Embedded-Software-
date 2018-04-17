#ifndef THREAH_H
#define THREAD_H

#include <signal.h>
#include <unistd.h>

#define DEFAULT_THREAD_ATTR ((void *)0)

pthread_mutex_t lock_accel ;
pthread_cond_t cond_var_accel;
sig_atomic_t accel_flag_glb;

typedef struct
{
        int t_id;
        char* plog_file;
        pthread_t main;
} threadTaskAttr;

void *AccelTask(void *pthread_inf);

#endif