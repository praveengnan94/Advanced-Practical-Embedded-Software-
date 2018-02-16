#include "threads.h"


threadinf actualinfo;

void *childThread1(void *threadp)
{
	int i;
    pthread_t thread;
    cpu_set_t cpuset;
    struct timespec start_time = {0, 0};
    struct timespec finish_time = {0, 0};
    struct timespec thread_dt = {0, 0};
    threadinf *threadParams = (threadinf *)threadp;

    clock_gettime(CLOCK_REALTIME, &start_time);
    printf("childThread1 FILE NAME Is %s\n",threadParams->logfilename );

    //open text file, read all characters and insert in array
	FILE *fp;
	fp=fopen("Valentinesday.txt", "r");

	if(fp==NULL)
	{
		perror("Failed to open file ");

	}
	char c;
	while((c = fgetc(fp)) != EOF)
	{
		// printf("%c",c);
		insert(c,head);
	}

 	// insert('b',head);
	// insert('B',head);
	// insert('a',head);

	print(head);
}

void *childThread2(void *threadp)
{
	int i;
    pthread_t thread;
    cpu_set_t cpuset;
    struct timespec start_time = {0, 0};
    struct timespec finish_time = {0, 0};
    struct timespec thread_dt = {0, 0};
    threadinf *threadParams = (threadinf *)threadp;

    clock_gettime(CLOCK_REALTIME, &start_time);
    printf("childThread2 FILE NAME Is %s\n",threadParams->logfilename );
}


void *masterThread(void *threadp)
{
	int i;
    pthread_t thread;
    cpu_set_t cpuset;
    struct timespec start_time = {0, 0};
    struct timespec finish_time = {0, 0};
    threadinf *threadParams = (threadinf *)threadp;

    clock_gettime(CLOCK_REALTIME, &start_time);
    printf("masterThread FILE NAME Is %s\n",threadParams->logfilename );
    // printf("\nPOSIX thread idx=%d started at time %ld\n", threadParams->threadIdx, start_time.tv_sec);

    threadParams->pid=pthread_self();

    // CPU_ZERO(&cpuset);
    // threadParams->tid = (pid_t) syscall (SYS_gettid);
 

    clock_gettime(CLOCK_REALTIME, &finish_time);
    // printf("\nThread idx=%d finsihed at time %ld\n", threadParams->threadIdx, finish_time.tv_sec);

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

    // i=2;
	   //     rc=pthread_attr_init(&rt_sched_attr[i]);
	   //     rc=pthread_attr_setinheritsched(&rt_sched_attr[i], PTHREAD_EXPLICIT_SCHED);
	   //     rc=pthread_attr_setschedpolicy(&rt_sched_attr[i], SCHED_FIFO);

	   //     rt_param[i].sched_priority=rt_max_prio-i-1;
	   //     pthread_attr_setschedparam(&rt_sched_attr[i], &rt_param[i]);

	   //     pthread_create(&threads[i],   // pointer to thread descriptor
	   //                    (void *)0,     // use default attributes
	   //                    childThread2, // thread function entry point
	   //                    (void *)&(actualinfo) // parameters to pass in
	   //                   );

   pthread_join(threads[1], NULL);
   

    //    pthread_join(threads[2], NULL);

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


   printf("\nTEST COMPLETE\n");
}