/***************************************************************
* AUTHOR  : Praveen Gnanaseakran
* DATE    : 03/08/2018
* DESCRITPTION  : main files
                  
* HEADER FILES  : main.h
****************************************************************/

#include "main.h"

/************************************************************/
int main(int argc, char *argv[]) {

  if (argc > 1) {
    fileid = (char *)malloc(sizeof(argv[1]));
    strcpy(fileid, argv[1]);
  } else {
    fileid = (char *)malloc(sizeof(DEFAULT_FILE_NAME));
    strcpy(fileid, DEFAULT_FILE_NAME);
  }
  
  // printf("LOGFILE name %s\n", fileid);

  magneto_close_flag=1;
  magneto_heartbeat_flag=0;

  // sigset_t mask_bit, all_signals_mask; // set of signals
  
  // sigfillset(&all_signals_mask);
  
  // ret =pthread_sigmask(SIG_SETMASK, &all_signals_mask, NULL); 

  // if (ret == -1) 
  // {
  //   perror("MASKING ERROR");
  //   return -1;
  // }

  struct sigaction sigactn;
  sigemptyset(&sigactn.sa_mask);

  sigactn.sa_handler = magneto_heartbeat_handl;
  ret = sigaction(MAGNETO_SIG_HEARTBEAT, &sigactn, NULL);
  if (ret == -1) {
    perror("SIGACTION ERROR");
    return -1;
  }

  int ret;

  pthread_t magneto,logger,comm;
  threadTaskAttr magneto_task_info,logger_task_info,comm_task_info;

  magneto_task_info.t_id=1;
  magneto_task_info.main=pthread_self();

  logger_task_info.t_id=2;
  logger_task_info.main=pthread_self();

  comm_task_info.t_id=3;
  comm_task_info.main=pthread_self();

  ret = pthread_create(&magneto, DEFAULT_THREAD_ATTR, MagnetoTask, (void *)&(magneto_task_info));
  if (ret != 0) {
    printf("Pthread error:%s\n", strerror(errno));
    return -1;
  }

  ret = pthread_create(&logger, DEFAULT_THREAD_ATTR, LoggerTask, (void *)&(logger_task_info));
  if (ret != 0) {
    printf("Pthread error:%s\n", strerror(errno));
    return -1;
  }

  ret = pthread_create(&comm, DEFAULT_THREAD_ATTR, CommTask, (void *)&(comm_task_info));
  if (ret != 0) {
    printf("Pthread error:%s\n", strerror(errno));
    return -1;
  }
  // UNITERRUPTIBLE_SLEEP(1); // allow other threads to initialize
  // sigaddset(&mask_bit, MAGNETO_SIGNAL_OPT);

  // ret =pthread_sigmask(SIG_SETMASK, &mask_bit, NULL); // if non NULL prev val of signal mask_bit stored here
  // if (ret == -1) {
  //   printf("Main pthread_sigmask:%s\n", strerror(errno));
  //   return -1;
  // }
  // char killoption;

  while (1) 
  {

    // check HB signals every 5 seconds for 5 tasks
    UNITERRUPTIBLE_SLEEP(1);

    if (magneto_exit_flag == 0) {
      if (magneto_heartbeat_flag == 0)
        printf("Magneto task no heartbeat\n");
      else {
        printf("[M]\n");
        magneto_heartbeat_flag = 0;
      }
    }


  //   fflush(stdout);

  }
  pthread_join(magneto, NULL);
  pthread_join(logger, NULL);
  pthread_join(comm, NULL);
  return 0;
}


void magneto_heartbeat_handl(int sig) {
  if (sig == MAGNETO_SIG_HEARTBEAT) {
    magneto_heartbeat_flag = 1;
  }
}

