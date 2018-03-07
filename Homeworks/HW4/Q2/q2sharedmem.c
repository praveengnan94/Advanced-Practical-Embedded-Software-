/***************************************************************
* AUTHOR  : Praveen Gnanasekaran
* DATE    : 03/06/2018
* DESCRIPTION  : This program explores various shared memory mechanism to communicate in Linux
* HEADER FILES  : q2.h
****************************************************************/

#include "q2.h"

typedef struct {
        char led_status[10];
        char message[10];
} msg_struct_mem;

msg_struct_mem actual_msg_mem;

void sharedmem()
{

    printf("Shared Memory Example\n");
    int shmem_fd;/*shared memory file desxriptor*/
    const char name[] = "sharedobj";/*name of the shared mem object*/
    void* mem_obj;

    msg_struct_mem child_message[1];
    strcpy(child_message->message,"CHILD");
    strcpy(child_message->led_status,"LEDON");
    
    msg_struct_mem parent_message[1];
    strcpy(parent_message->message,"PARENT");
    strcpy(parent_message->led_status,"LEDOFF");
    
    msg_struct_mem* message_buf = (msg_struct_mem*)malloc(sizeof(msg_struct_mem));
    if(message_buf==NULL) 
    {
        printf("malloc Error: %s\n", strerror(errno)); 
        exit(1);
    }

    switch(fork()) {
    case -1: printf("fork error\n");
            exit(1);
            break;

    case 0://child process-reads the shared memory
            shmem_fd = shm_open(name,O_CREAT|O_RDWR,0666);/*create shared mem obj*/
            ftruncate(shmem_fd,BUFFER_SIZE);/*config size of shared mem object*/
            mem_obj = mmap(0, BUFFER_SIZE,PROT_READ|PROT_WRITE,MAP_SHARED, shmem_fd,0);
            if(mem_obj == NULL) 
            {
                printf("mmap Error: %s\n", strerror(errno)); 
                exit(1);
            }

            printf("PARENT SAYS:%s;led_status:%s\n", ((msg_struct_mem*)mem_obj)->message,((msg_struct_mem*)mem_obj)->led_status);

            if(strcmp((((msg_struct_mem*)mem_obj)->led_status),"LEDOFF")==0)
                system("echo 0 > /sys/class/leds/beaglebone:green:usr0/brightness");
            if(strcmp((((msg_struct_mem*)mem_obj)->led_status),"LEDON")==0)
                system("echo 1 > /sys/class/leds/beaglebone:green:usr0/brightness");

            /**clear memory***/
            bzero(mem_obj,sizeof(msg_struct_mem));
            if(memcpy(mem_obj,child_message,sizeof(child_message)) == NULL) 
            {
                printf("memcpy Error: %s\n", strerror(errno)); 
                exit(1);
            }
            else 
              printf("Written from child\n");

            sleep(1);
            shm_unlink(name);
            break;


    default://parent process- writes to the shared memory
            shmem_fd = shm_open(name,O_CREAT|O_RDWR,0666);/*create shared mem obj*/
            ftruncate(shmem_fd,BUFFER_SIZE);/*config size of shared mem object*/
            /***memory map the shared memory in the address space of the calling process***/
            mem_obj = mmap(0,
                              BUFFER_SIZE,PROT_WRITE | PROT_READ,
                              MAP_SHARED,shmem_fd,
                              0);
            if(mem_obj == NULL)
            {
                printf("mmap Error: %s\n", strerror(errno)); 
                exit(1);
            } 

            /**clear memory***/
            bzero(mem_obj,sizeof(msg_struct_mem));

            if(memcpy(mem_obj,parent_message,sizeof(parent_message))==NULL) 
            {
              printf("memcpy Error: %s\n", strerror(errno)); 
              exit(1);
            }
            else 
              printf("Written from parent\n");

            sleep(2);  

            printf("CHILD SAYS:%s;led_status:%s\n", ((msg_struct_mem*)pshmem_obj)->message,((msg_struct_mem*)pshmem_obj)->led_status);

            if(strcmp((((msg_struct_mem*)mem_obj)->led_status),"LEDOFF")==0)
                system("echo 0 > /sys/class/leds/beaglebone:green:usr0/brightness");
            if(strcmp((((msg_struct_mem*)mem_obj)->led_status),"LEDON")==0)
                system("echo 1 > /sys/class/leds/beaglebone:green:usr0/brightness");

            shm_unlink(name);
            break;
    }
}