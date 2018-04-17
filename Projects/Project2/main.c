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

  int ret;

  pthread_t accel,magneto,logger;
  threadTaskAttr accel_task_info,magneto_task_info,logger_task_info;
  accel_task_info.t_id = 1;
  accel_task_info.main = pthread_self();

  magneto_task_info.t_id=2;
  magneto_task_info.main=pthread_self();

  logger_task_info.t_id=3;
  logger_task_info.main=pthread_self();

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

  UNITERRUPTIBLE_SLEEP(1); // allow other threads to initialize


  // ret =pthread_sigmask(SIG_SETMASK, &mask_bit, NULL); // if non NULL prev val of signal mask_bit stored here
  // if (ret == -1) {
  //   printf("Main pthread_sigmask:%s\n", strerror(errno));
  //   return -1;
  // }
  // char killoption;

  while (1) {

    // check HB signals every 5 seconds for 5 tasks
    UNITERRUPTIBLE_SLEEP(5);

    if (accel_exit_flag == 0) {
      if (accel_heartbeat_flag == 0)
        printf("Accel task no heartbeat\n");
      else {
        printf("Accel task alive\n");
        accel_heartbeat_flag = 0;
      }
    }

  //   fflush(stdout);

  }
  pthread_join(accel, NULL);
  pthread_join(magneto, NULL);
  pthread_join(logger, NULL);
  return 0;
}

void accel_heartbeat_handl(int sig) {
  if (sig == ACCEL_SIG_HEARTBEAT) {
    printf("ACELELL HEEART\n");
    accel_heartbeat_flag = 1;
  }
}