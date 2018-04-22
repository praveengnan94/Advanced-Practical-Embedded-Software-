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
  accel_close_flag = 1;
  accel_heartbeat_flag=0;

  magneto_close_flag=1;
  magneto_heartbeat_flag=0;

  logger_close_flag=1;
  logger_heartbeat_flag=0;

  comm_close_flag=1;
  comm_heartbeat_flag=0;

  sigset_t mask_bit, all_signals_mask; // set of signals
  
  sigfillset(&all_signals_mask);
  
  ret =pthread_sigmask(SIG_SETMASK, &all_signals_mask, NULL); 

  if (ret == -1) 
  {
    perror("MASKING ERROR");
    return -1;
  }

  struct sigaction sigactn;
  sigemptyset(&sigactn.sa_mask);
  sigactn.sa_handler = accel_heartbeat_handl;
  ret = sigaction(ACCEL_SIG_HEARTBEAT, &sigactn, NULL);
  if (ret == -1) {
    perror("SIGACTION ERROR");
    return -1;
  }

  sigemptyset(&sigactn.sa_mask);
  sigactn.sa_handler = magneto_heartbeat_handl;
  ret = sigaction(MAGNETO_SIG_HEARTBEAT, &sigactn, NULL);
  if (ret == -1) {
    perror("SIGACTION ERROR");
    return -1;
  }

  sigemptyset(&sigactn.sa_mask);
  sigactn.sa_handler = logger_heartbeat_handl;
  ret = sigaction(LOGGER_SIG_HEARTBEAT, &sigactn, NULL);
  if (ret == -1) {
    perror("SIGACTION ERROR");
    return -1;
  }

  int ret;

  pthread_t accel,magneto,logger,comm;
  threadTaskAttr accel_task_info,magneto_task_info,logger_task_info,comm_task_info;
  accel_task_info.t_id = 1;
  accel_task_info.main = pthread_self();

  magneto_task_info.t_id=2;
  magneto_task_info.main=pthread_self();

  logger_task_info.t_id=3;
  logger_task_info.main=pthread_self();

  comm_task_info.t_id=3;
  comm_task_info.main=pthread_self();

  ret = pthread_create(&accel, DEFAULT_THREAD_ATTR, AccelTask, (void *)&(accel_task_info));
  if (ret != 0) {
    printf("Pthread error:%s\n", strerror(errno));
    return -1;
  }

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

  UNITERRUPTIBLE_SLEEP(1); // allow other threads to initialize


  ret =pthread_sigmask(SIG_SETMASK, &mask_bit, NULL); // if non NULL prev val of signal mask_bit stored here
  if (ret == -1) {
    printf("Main pthread_sigmask:%s\n", strerror(errno));
    return -1;
  }
  char killoption;

  sigaddset(&mask_bit, ACCEL_SIGNAL_OPT);
  sigaddset(&mask_bit, LOGGER_SIGNAL_OPT);
  sigaddset(&mask_bit, MAGNETO_SIGNAL_OPT);
  sigaddset(&mask_bit, COMM_SIGNAL_OPT);
  // signal(SIGINT, SIGNAL_INTERRUPT_HANDL);

  uint8_t initialize;
  char initialize_msg[8][4096];

  ret = init_timer(); 

  if (ret == -1) 
  {
    initialize = 0;
    sprintf(&(initialize_msg[1][0]), "Failure Temptask init_timer \n");
  } 
  else 
  {
    sprintf(&(initialize_msg[1][0]), "Success Temptask init_timer \n");
  }


  while (1) 
  {

    // check HB signals every 5 seconds for 5 tasks
    UNITERRUPTIBLE_SLEEP(3);

    if (accel_exit_flag == 0) {
      if (accel_heartbeat_flag == 0)
        printf("Accel task no heartbeat\n");
      else {
        printf("[A]\n");
        accel_heartbeat_flag = 0;
      }
    }

    if (magneto_exit_flag == 0) {
      if (magneto_heartbeat_flag == 0)
        printf("Magneto task no heartbeat\n");
      else {
        printf("[M]\n");
        magneto_heartbeat_flag = 0;
      }
    }

    if (logger_exit_flag == 0) {
      if (logger_heartbeat_flag == 0)
        printf("Logger task no heartbeat\n");
      else {
        printf("[L]\n");
        logger_heartbeat_flag = 0;
      }
    }

  //   fflush(stdout);

  }
  pthread_join(accel, NULL);
  pthread_join(magneto, NULL);
  pthread_join(logger, NULL);
  pthread_join(comm, NULL);
  return 0;
}

void accel_heartbeat_handl(int sig) {
  if (sig == ACCEL_SIG_HEARTBEAT) {
    accel_heartbeat_flag = 1;
  }
}

void logger_heartbeat_handl(int sig) {
  if (sig == LOGGER_SIG_HEARTBEAT) {
    logger_heartbeat_flag = 1;
  }
}

void magneto_heartbeat_handl(int sig) {
  if (sig == MAGNETO_SIG_HEARTBEAT) {
    magneto_heartbeat_flag = 1;
  }
}

void comm_heartbeat_handl(int sig) {
  if (sig == COMM_SIG_HEARTBEAT) {
    comm_heartbeat_flag = 1;
  }
}