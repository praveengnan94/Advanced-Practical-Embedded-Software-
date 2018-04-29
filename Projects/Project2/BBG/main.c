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

  // magneto_close_flag=1;
  // magneto_heartbeat_flag=0;

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

  while (1) 
  {
    // check HB signals every 5 seconds for 5 tasks
    UNITERRUPTIBLE_SLEEP(1);

    if (magneto_exit_flag == 0) {
      if ((magneto_heartbeat_flag==1)&&(i2c_glb_pass==1))
      {
        printf("[M]\n");
        magneto_heartbeat_flag = 0;
      }
      else {
        printf("NOO [M]\n");
      }
    }
  }
  pthread_join(magneto, NULL);
  pthread_join(logger, NULL);
  pthread_join(comm, NULL);
  return 0;
}


// void magneto_heartbeat_handl(int sig) {
//   if (sig == MAGNETO_SIG_HEARTBEAT) {
//     if(i2c_glb_pass!=-1)
//     magneto_heartbeat_flag = 1;
//     else if(i2c_glb_pass==-1)
//       magneto_heartbeat_flag=0;
//   }
// }

