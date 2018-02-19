/***************************************************************
* AUTHOR  : Praveen Gnanasekaran
* DATE    : 02/18/2018
* DESCRITPTION  : This program creates a thread program which creates three threads, searches a text file and 
                  accepts user signals to exit thread after writing to a log file
      
* HEADER FILES  : threads.h
****************************************************************/


#include "threads.h"

threadinf actualinfo;

void *childThread1(void *threadp)
{
	int i;
    pthread_t thread;
    cpu_set_t cpuset;
    FILE *fp;
    struct timespec start_time = {0, 0};
    struct timespec finish_time = {0, 0};
    struct timespec thread_dt = {0, 0};
    threadinf *threadParams = (threadinf *)threadp;
    
    if(signal(SIGUSR1,child1_sigHandler)==SIG_ERR)
      printf("Signal 1 error\n");

    clock_gettime(CLOCK_REALTIME, &start_time);
    printf("childThread1 FILE NAME Is %s\n",threadParams->logfilename );


    threadParams->pid=getpid();
    threadParams->tid =pthread_self();

    pthread_mutex_lock(&mutexlock);
    fp=fopen(threadParams->logfilename,"a+");

      if(fp==NULL)
      {
        perror("Error opening file");
        exit(1);
      }

    sprintf(filestring,"CHILD THREAD 1 POSIX id=%ld Linux id=%d \n", threadParams->pid,threadParams->tid);
    fwrite(filestring,sizeof(char),strlen(filestring),fp);
    
    sprintf(filestring,"Start time child1 %ld\n", start_time.tv_sec);
    fwrite(filestring,sizeof(char),strlen(filestring),fp);
    fclose(fp); //causes seg fault
    pthread_mutex_unlock(&mutexlock); 

    //open text file, read all characters and insert in array
	FILE *fp1;
  
	fp1=fopen("Valentinesday.txt", "r");

	if(fp1==NULL)
	{
		perror("Failed to open file ");

	}

	char c;
	while((c = fgetc(fp1)) != EOF)
	{
    if(glb_var_sig1==0)
		  insert(c,head);
    else
    {
      pthread_mutex_lock(&mutexlock);
      fp=fopen(threadParams->logfilename,"a+");

      if(fp==NULL)
      {
        perror("Error opening file");
        exit(1);
      }
      clock_gettime(CLOCK_REALTIME, &finish_time);
      sprintf(filestring,"USR command received at time %ld. Exiting child 1\n", finish_time.tv_sec);
      fwrite(filestring,sizeof(char),strlen(filestring),fp);
      fclose(fp);
      fclose(fp1);
      pthread_mutex_unlock(&mutexlock); 
      pthread_exit(NULL);
    }
	}

  pthread_mutex_lock(&mutexlock);
  fp=fopen(threadParams->logfilename,"a+");

  if(fp==NULL)
  {
    perror("Error opening file");
    exit(1);
  }

  //Find all characters which have key value as 3
  strcpy(filestring,"Characters which are repeated thrice are ");
  fwrite(filestring,sizeof(char),strlen(filestring),fp);
  fclose(fp);
  pthread_mutex_unlock(&mutexlock); 

  int cnt=0;
  struct Node*  temp=head;
  int val;

  while(temp!=NULL)
  {
    if(glb_var_sig1==0)
    {
      val=temp->key;
      temp=temp->next;
      if(val==3)
      {
        pthread_mutex_lock(&mutexlock);
        fp=fopen(threadParams->logfilename,"a+");
        sprintf(filestring,"%c, ", cnt+65);
        fwrite(filestring,sizeof(char),strlen(filestring),fp);
        fclose(fp);
        pthread_mutex_unlock(&mutexlock); 
      }
      cnt++;
    }
    else
    {
      clock_gettime(CLOCK_REALTIME, &finish_time);
      sprintf(filestring,"USR1 command received at time %ld. Exiting child 1\n", finish_time.tv_sec);
      fwrite(filestring,sizeof(char),strlen(filestring),fp);
      fclose(fp);
      pthread_mutex_unlock(&mutexlock); 
      pthread_exit(NULL);
    }
  }
  

  pthread_mutex_lock(&mutexlock);
  fp=fopen(threadParams->logfilename,"a+");
  strcpy(filestring,"\n");
  fwrite(filestring,sizeof(char),strlen(filestring),fp);

  clock_gettime(CLOCK_REALTIME, &finish_time);
  sprintf(filestring,"Finish time child1 %ld\n", finish_time.tv_sec);
  fwrite(filestring,sizeof(char),strlen(filestring),fp);
  fclose(fp);
  pthread_mutex_unlock(&mutexlock); 

	print(head);
}

void *childThread2(void *threadp)
{
	int i;
  FILE *fp; 
    pthread_t thread;
    cpu_set_t cpuset;
    struct timespec start_time = {0, 0};
    struct timespec finish_time = {0, 0};
    struct timespec thread_dt = {0, 0};
    threadinf *threadParams = (threadinf *)threadp;

    clock_gettime(CLOCK_REALTIME, &start_time);

    if(signal(SIGUSR2,child2_sigHandler)==SIG_ERR)
      printf("Signal 2 error\n");

    threadParams->pid=getpid();
    threadParams->tid = pthread_self();

    pthread_mutex_lock(&mutexlock);
    fp=fopen(threadParams->logfilename,"a+");

      if(fp==NULL)
      {
        perror("Error opening file");
        exit(1);
      }

    sprintf(filestring,"CHILD THREAD 2 POSIX id=%ld Linux id=%d \n", threadParams->pid,threadParams->tid);
    fwrite(filestring,sizeof(char),strlen(filestring),fp);
    
    sprintf(filestring,"Start time child2 %ld\n", start_time.tv_sec);
    fwrite(filestring,sizeof(char),strlen(filestring),fp);
    fclose(fp); //causes seg fault
    pthread_mutex_unlock(&mutexlock);

    //get thread id ,pid and write to log file
    struct timespec tim, tim2;
     tim.tv_sec = 0;
     tim.tv_nsec = 1000;

    while(1)
    {
      if(glb_var_sig2==0)
      {
        clock_gettime(CLOCK_REALTIME, &start_time);
	      // 	shell command to find cpu utilization and write to log file
        pthread_mutex_lock(&mutexlock);
        fp=fopen(threadParams->logfilename,"a+");

          if(fp==NULL)
          {
            perror("Error opening file");
            exit(1);
          }
          sprintf(filestring,"Time after 100ms %ld\n", start_time.tv_sec);
          fwrite(filestring,sizeof(char),strlen(filestring),fp);

        sprintf(filestring,"%d",system("uptime > htop"));
        FILE *htop;

        htop=fopen("htop","r");
        
        while(1)        
        {
          if (fgets(filestring,300, htop) == NULL) 
          {
              break;
          }
          fwrite(filestring,sizeof(char),strlen(filestring),fp);
        }

        fclose(htop);
        fclose(fp); //causes seg fault
        pthread_mutex_unlock(&mutexlock);

	    	if(nanosleep(&tim , &tim2) < 0 )   
         {
            printf("Nano sleep system call failed \n");
            exit(1);
         }

        // printf("Slept for 100ms \n");
    	}
    	else
    	{
        pthread_mutex_lock(&mutexlock);

        fp=fopen(threadParams->logfilename,"a+");
        if(fp==NULL)
        {
          perror("Error opening file");
          exit(1);
        }

    		clock_gettime(CLOCK_REALTIME, &finish_time);
        sprintf(filestring,"USR2 command received at time %ld. Exiting child 2\n", finish_time.tv_sec);
        fwrite(filestring,sizeof(char),strlen(filestring),fp);
        fclose(fp);

        pthread_mutex_unlock(&mutexlock);
    		pthread_exit(NULL);
    	}
    }
}


void *masterThread(void *threadp)
{
    int i;
    pthread_t thread;
    struct timespec start_time = {0, 0};
    struct timespec finish_time = {0, 0};
    threadinf *threadParams = (threadinf *)threadp;
    FILE *fp;

    clock_gettime(CLOCK_REALTIME, &start_time);
    printf("masterThread FILE NAME Is %s\n",threadParams->logfilename );

    pthread_mutex_lock(&mutexlock); 

    fp=fopen(threadParams->logfilename,"a+");
    if(fp==NULL)
    {
      perror("Error opening file");
      exit(1);
    }

    threadParams->pid=getpid();
    threadParams->tid = pthread_self();

    sprintf(filestring,"MASTER THREAD POSIX id=%ld Linux id=%d \n", threadParams->pid,threadParams->tid);
    fwrite(filestring,sizeof(char),strlen(filestring),fp);
    
    sprintf(filestring,"Start time master %ld\n", start_time.tv_sec);
    fwrite(filestring,sizeof(char),strlen(filestring),fp);
    fclose(fp); //causes seg fault
    pthread_mutex_unlock(&mutexlock); 

    i=1;
	       rc=pthread_attr_init(&rt_sched_attr[i]);
	       rc=pthread_attr_setinheritsched(&rt_sched_attr[i], PTHREAD_EXPLICIT_SCHED);
	       rc=pthread_attr_setschedpolicy(&rt_sched_attr[i], SCHED_FIFO);

	       rt_param[i].sched_priority=rt_max_prio-i-1;
	       pthread_attr_setschedparam(&rt_sched_attr[i], &rt_param[i]);

	       pthread_create(&threads[i],   // pointer to thread descriptor
	                      (void *)0,     // use default attributes
	                      childThread1, // thread function entry point
	                      (void *)&(actualinfo) // parameters to pass in
	                     );

    i=2;
	       rc=pthread_attr_init(&rt_sched_attr[i]);
	       rc=pthread_attr_setinheritsched(&rt_sched_attr[i], PTHREAD_EXPLICIT_SCHED);
	       rc=pthread_attr_setschedpolicy(&rt_sched_attr[i], SCHED_FIFO);

	       rt_param[i].sched_priority=rt_max_prio-i-1;
	       pthread_attr_setschedparam(&rt_sched_attr[i], &rt_param[i]);

	       pthread_create(&threads[i],   // pointer to thread descriptor
	                      (void *)0,     // use default attributes
	                      childThread2, // thread function entry point
	                      (void *)&(actualinfo) // parameters to pass in
	                     );

   pthread_join(threads[1], NULL);
   pthread_join(threads[2], NULL);


   fp=fopen(threadParams->logfilename,"a+");
    if(fp==NULL)
    {
      perror("Error opening file");
      exit(1);
    }

   pthread_mutex_lock(&mutexlock);
   clock_gettime(CLOCK_REALTIME, &finish_time);
   sprintf(filestring,"Finish time master %ld\n", finish_time.tv_sec);
   fwrite(filestring,sizeof(char),strlen(filestring),fp);
   fclose(fp);
   pthread_mutex_unlock(&mutexlock);
    // pthread_exit(&sum);
}

int main (int argc, char *argv[])
{
   
   int i, scope;
   cpu_set_t cpuset;

   if(argc!=2)
   {
   	printf("Please enter log filename\n");
   	exit(1);
   }
   

   CPU_ZERO(&cpuset);
   for(i=0; i < NUM_CPUS; i++)
       CPU_SET(i, &cpuset);

   mainpid=getpid();
   for(i=0;i<26;i++) //create 26 lists with values as 0
		push(&head, 0);
   rt_max_prio = sched_get_priority_max(SCHED_FIFO);
   rt_min_prio = sched_get_priority_min(SCHED_FIFO);

   rc=sched_getparam(mainpid, &main_param);
   main_param.sched_priority=rt_max_prio;
   rc=sched_setscheduler(getpid(), SCHED_FIFO, &main_param);
   if(rc < 0) perror("main_param");


   rc= pthread_mutex_init(&mutexlock,&mutexattr);
    if(rc!=0)
    {
      perror("MUTEX ERROR ");
    }

   pthread_attr_getscope(&main_attr, &scope);
	
	i=0;
       rc=pthread_attr_init(&rt_sched_attr[i]);
       rc=pthread_attr_setinheritsched(&rt_sched_attr[i], PTHREAD_EXPLICIT_SCHED);
       rc=pthread_attr_setschedpolicy(&rt_sched_attr[i], SCHED_FIFO);

       rt_param[i].sched_priority=rt_max_prio-i-1;
       pthread_attr_setschedparam(&rt_sched_attr[i], &rt_param[i]);
       strcpy(actualinfo.logfilename,argv[1]);

       pthread_create(&threads[0],   // pointer to thread descriptor
                      (void *)0,     // use default attributes
                      masterThread, // thread function entry point
                      (void *)&(actualinfo) // parameters to pass in
                     );

    pthread_join(threads[0], NULL);

    pthread_mutex_destroy(&mutexlock);

   printf("\nTEST COMPLETE\n");
}