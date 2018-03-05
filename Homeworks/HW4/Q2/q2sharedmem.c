#include "q2.h"

void sharedmem()
{

    printf("Shared Memory Example\n");
    //const int SIZE = 4096;
    int shmem_fd;/*shared memory file desxriptor*/
    const char name[] = "OS";/*name of the shared mem object*/
    //const char message1[] = "Hello";
    //const char message2[] = "World";
    void* pshmem_obj;

    switch(fork()) {
    case -1: printf("fork error\n");
            return -1;
            break;

    case 0://child process-reads the shared memory
            sleep(1);//let the parent write first
            printf("Entering Child, PID:%d\n",getpid());
            shmem_fd = shm_open(name,O_CREAT|O_RDWR,0666);/*create shared mem obj*/
            ftruncate(shmem_fd,BUF_SIZE);/*config size of shared mem object*/
            pshmem_obj = mmap(0,
                              BUF_SIZE,PROT_READ|PROT_WRITE,
                              MAP_SHARED,
                              shmem_fd,
                              0);
            if(pshmem_obj == NULL) PRINT_ERR("mmap");

            printf("Read in child:%s; led_status:%d\n",
                   ((msg_struct*)pshmem_obj)->message,
                   ((msg_struct*)pshmem_obj)->led_status );

            /**clear memory***/
            bzero(pshmem_obj,sizeof(msg_struct));
            if(memcpy(pshmem_obj,child_message,sizeof(child_message)) == NULL) {PRINT_ERR("memcpy");}
            else printf("Written from child\n");
            sleep(1);
            shm_unlink(name);
            break;


    default://parent process- writes to the shared memory
            printf("Entering Parent, PID:%d\n",getpid());
            shmem_fd = shm_open(name,O_CREAT|O_RDWR,0666);/*create shared mem obj*/
            ftruncate(shmem_fd,BUF_SIZE);/*config size of shared mem object*/
            /***memory map the shared memory in the address space of the calling process***/
            pshmem_obj = mmap(0,
                              BUF_SIZE,PROT_WRITE | PROT_READ,
                              MAP_SHARED,shmem_fd,
                              0);
            if(pshmem_obj == NULL) PRINT_ERR("mmap");

            /****Write to the shared memory object******/
            /**clear memory***/
            bzero(pshmem_obj,sizeof(msg_struct));

            if(memcpy(pshmem_obj,parent_message,sizeof(parent_message))==NULL) {PRINT_ERR("memcpy");}
            else printf("Written from parent\n");
            sleep(2);  //allow child to complete read and write before parent reads
            printf("Read in Parent :%s; led_status:%d\n",
                   ((msg_struct*)pshmem_obj)->message,
                   ((msg_struct*)pshmem_obj)->led_status );
            shm_unlink(name);
            break;
    }
}