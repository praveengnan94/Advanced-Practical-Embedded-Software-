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
  READY_LED;
  LED_ON;
  while (magneto_exit_flag==0) 
  {
    // check HB signals every 1 seconds for 1 task
    UNITERRUPTIBLE_SLEEP(1);

    killoption=getc(stdin);
      if(killoption=='E'){
          printf("CLOSING ALL TASKS\n");
          magneto_exit_flag=1;
      }

  }
  pthread_join(magneto, NULL);
  pthread_join(logger, NULL);
  pthread_join(comm, NULL);
  return 0;
}

