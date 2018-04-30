/***************************************************************
* AUTHOR  : Praveen Gnanasekaran
* DATE    : 04/28/2018
* DESCRITPTION  : threads.h
                  
* SOURCE FILES  : threads.c
****************************************************************/
#ifndef THREAH_H
#define THREAD_H

#include <signal.h>
#include <unistd.h>

#define DEFAULT_THREAD_ATTR ((void *)0)

pthread_mutex_t lock_accel ;
pthread_cond_t cond_var_accel;

pthread_mutex_t lock_magneto ;
pthread_cond_t cond_var_magneto;

pthread_mutex_t lock_logger ;
pthread_cond_t cond_var_logger;

pthread_mutex_t lock_comm ;
pthread_cond_t cond_var_comm;

sig_atomic_t accel_flag_glb;
sig_atomic_t magneto_flag_glb;
sig_atomic_t logger_flag_glb;
sig_atomic_t comm_flag_glb;

typedef struct
{
        int t_id;
        char* plog_file;
        pthread_t main;
} threadTaskAttr;


#endif