/***************************************************************
* AUTHOR  : Praveen Gnanasekaran
* DATE    : 03/06/2018
* DESCRIPTION  : This program explores various IPC SOCKET mechanism to communicate in Linux
* REFERENCE : https://users.cs.cf.ac.uk/Dave.Marshall/C/node28.html
* HEADER FILES  : q2.h
****************************************************************/

#include "q2.h"

typedef struct {
        char led_status[10];
        char message[50];
} msg_struct_sock;

msg_struct_sock actual_msg_sock;

int done, n;
char buffer[50];
#define SOCK_PATH "echo_socket"

void sock()
{
    printf("Running sockets\n");
    int s, s2, t, len;
    struct sockaddr_un local, remote;
    char str[100];

    msg_struct_sock child_message[1];
    strcpy(child_message->message,"CHILD MESSAGE");
    strcpy(child_message->led_status,"LEDON");
    

    msg_struct_sock parent_message[1];
    strcpy(parent_message->message,"PARENT MESSAGE");
    strcpy(parent_message->led_status,"LEDOFF");
    

    msg_struct_sock* message_buf = (msg_struct_sock*)malloc(sizeof(msg_struct_sock));
    if(message_buf==NULL) 
    {
        printf("malloc Error: %s\n", strerror(errno)); 
        exit(1);
    }

    switch(fork()) 
    {
    case -1:
            printf("fork Error:%s\n",strerror(errno));
            break;

    case 0://child process - client

        if ((s = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) {
            perror("socket");
            exit(1);
        }


        remote.sun_family = AF_UNIX;
        strcpy(remote.sun_path, SOCK_PATH);
        len = strlen(remote.sun_path) + sizeof(remote.sun_family);
        if (connect(s, (struct sockaddr *)&remote, len) == -1) {
            perror("connect");
            exit(1);
        }


        // while(fgets(parent_message_recv, sizeof(parent_message_recv), stdin),!feof(stdin)) 
        {
            if (send(s, parent_message, sizeof(parent_message), 0) == -1) {
                perror("send");
                exit(1);
            }

            n = recv(s, message_buf, sizeof(message_buf), 0);
            if (n <= 0) {
                if (n < 0) perror("recv");
            }

            printf("PARENT SAYS:%s;led_status:%s\n", message_buf->message,message_buf->led_status);

            if(strcmp((message_buf->led_status),"LEDOFF")==0)
                system("echo 0 > /sys/class/leds/beaglebone:green:usr0/brightness");
            if(strcmp((message_buf->led_status),"LEDON")==0)
                system("echo 1 > /sys/class/leds/beaglebone:green:usr0/brightness");

            sleep(3);

            if (send(s, "DONE", strlen("DONE"), 0) == -1) {
                perror("send");
                exit(1);
            }
        }

        close(s);

        break;

    default://parent - server
        
        if ((s = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) {
            perror("socket");
            exit(1);
        }

        local.sun_family = AF_UNIX;
        strcpy(local.sun_path, SOCK_PATH);
        unlink(local.sun_path);
        len = strlen(local.sun_path) + sizeof(local.sun_family);
        if (bind(s, (struct sockaddr *)&local, len) == -1) {
            perror("bind");
            exit(1);
        }

        if (listen(s, 5) == -1) {
            perror("listen");
            exit(1);
        }

        for(;;) {
            printf("Waiting for a connection...\n");
            t = sizeof(remote);
            if ((s2 = accept(s, (struct sockaddr *)&remote, &t)) == -1) {
                perror("accept");
                exit(1);
            }



            n = recv(s2, message_buf, sizeof(message_buf), 0);
            if (n <= 0) {
                if (n < 0) perror("recv");
            }
            printf("CHILD SAYS:%s;led_status:%s\n",message_buf->message,message_buf->led_status);

            if(strcmp((message_buf->led_status),"LEDOFF")==0)
                system("echo 0 > /sys/class/leds/beaglebone:green:usr0/brightness");
            if(strcmp((message_buf->led_status),"LEDON")==0)
                system("echo 1 > /sys/class/leds/beaglebone:green:usr0/brightness");

            sleep(3);

            if (send(s2, child_message, sizeof(child_message), 0) < 0) {
                perror("send");
                done = 1;
            }

            n = recv(s2, str, sizeof(str), 0);
            if (n <= 0) {
                if (n < 0) perror("recv");
            }


            close(s2);
        }
        break;
    }
}