#include "threads.h"


typedef struct threadinfo
{
	char logfilename[20];	
	pthread_t pid;
	pid_t tid;
}threadinf;

threadinf actualinfo;

void *masterThread(void *threadp)
{
	int sum=0, i;
    pthread_t thread;
    cpu_set_t cpuset;
    struct timespec start_time = {0, 0};
    struct timespec finish_time = {0, 0};
    struct timespec thread_dt = {0, 0};
    threadinf *threadParams = (threadinf *)threadp;

    clock_gettime(CLOCK_REALTIME, &start_time);
    printf("FILE NAME Is %s\n",threadParams->logfilename );
    // printf("\nPOSIX thread idx=%d started at time %ld\n", threadParams->threadIdx, start_time.tv_sec);

    threadParams->pid=pthread_self();

    // CPU_ZERO(&cpuset);
    // threadParams->tid = (pid_t) syscall (SYS_gettid);
 
    pthread_getaffinity_np(thread, sizeof(cpu_set_t), &cpuset);

    clock_gettime(CLOCK_REALTIME, &finish_time);
    // printf("\nThread idx=%d finsihed at time %ld\n", threadParams->threadIdx, finish_time.tv_sec);

    // i=1;
	   //     rc=pthread_attr_init(&rt_sched_attr[i]);
	   //     rc=pthread_attr_setinheritsched(&rt_sched_attr[i], PTHREAD_EXPLICIT_SCHED);
	   //     rc=pthread_attr_setschedpolicy(&rt_sched_attr[i], SCHED_FIFO);
	   //     rc=pthread_attr_setaffinity_np(&rt_sched_attr[i], sizeof(cpu_set_t), &cpuset);

	   //     rt_param[i].sched_priority=rt_max_prio-i-1;
	   //     pthread_attr_setschedparam(&rt_sched_attr[i], &rt_param[i]);
	   //     strcpy(actualinfo[i].logfilename,argv[1]);
	   //     actualinfo[i].threadIdx=i;

	   //     pthread_create(&threads[i],   // pointer to thread descriptor
	   //                    (void *)0,     // use default attributes
	   //                    childThread1, // thread function entry point
	   //                    (void *)&(actualinfo[i]) // parameters to pass in
	   //                   );

    // i=2;
   	// 	   rc=pthread_attr_init(&rt_sched_attr[i]);
	   //     rc=pthread_attr_setinheritsched(&rt_sched_attr[i], PTHREAD_EXPLICIT_SCHED);
	   //     rc=pthread_attr_setschedpolicy(&rt_sched_attr[i], SCHED_FIFO);
	   //     rc=pthread_attr_setaffinity_np(&rt_sched_attr[i], sizeof(cpu_set_t), &cpuset);

	   //     rt_param[i].sched_priority=rt_max_prio-i-1;
	   //     pthread_attr_setschedparam(&rt_sched_attr[i], &rt_param[i]);
	   //     strcpy(actualinfo[i].logfilename,argv[1]);
	   //     actualinfo[i].threadIdx=i;

	   //     pthread_create(&threads[i],   // pointer to thread descriptor
	   //                    (void *)0,     // use default attributes
	   //                    childThread2, // thread function entry point
	   //                    (void *)&(actualinfo[i]) // parameters to pass in
	   //                   );

    //    pthread_join(threads[1], NULL);
    //    pthread_join(threads[2], NULL);

    pthread_exit(&sum);
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

   rt_max_prio = sched_get_priority_max(SCHED_FIFO);
   rt_min_prio = sched_get_priority_min(SCHED_FIFO);

   rc=sched_getparam(mainpid, &main_param);
   main_param.sched_priority=rt_max_prio;
   rc=sched_setscheduler(getpid(), SCHED_FIFO, &main_param);
   if(rc < 0) perror("main_param");

   pthread_attr_getscope(&main_attr, &scope);
	
	i=0;
   // for(i=0; i < NUM_THREADS; i++)
   {
       rc=pthread_attr_init(&rt_sched_attr[i]);
       rc=pthread_attr_setinheritsched(&rt_sched_attr[i], PTHREAD_EXPLICIT_SCHED);
       rc=pthread_attr_setschedpolicy(&rt_sched_attr[i], SCHED_FIFO);
       rc=pthread_attr_setaffinity_np(&rt_sched_attr[i], sizeof(cpu_set_t), &cpuset);

       rt_param[i].sched_priority=rt_max_prio-i-1;
       pthread_attr_setschedparam(&rt_sched_attr[i], &rt_param[i]);
       strcpy(actualinfo.logfilename,argv[1]);
       // actualinfo[i].threadIdx=i;

       pthread_create(&threads[i],   // pointer to thread descriptor
                      (void *)0,     // use default attributes
                      masterThread, // thread function entry point
                      (void *)&(actualinfo) // parameters to pass in
                     );
   }

      pthread_join(threads[0], NULL);

   printf("\nTEST COMPLETE\n");
}