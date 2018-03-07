// https://users.cs.cf.ac.uk/Dave.Marshall/C/node28.html

#include "q2.h"

typedef struct {
        uint8_t led_status;
        char message[50];
} msg_struct_sock;

msg_struct_sock actual_msg_sock;
int done, n;
char buffer[50];
#define SOCK_PATH "echo_socket"
void sock()
{
    int s, s2, t, len;
    struct sockaddr_un local, remote;
    char str[100];

    /*linux has Half duplex setting, thus file_descriptor[0] is always used for reading,file_descriptor[1] always used for writing*/
    msg_struct_sock child_message[1],child_message_recv[1];
    strcpy(child_message->message,"LEDON");
    child_message->led_status = 0;

    msg_struct_sock parent_message[1],parent_message_recv[1];
    strcpy(parent_message->message,"LEDOFF");
    parent_message->led_status = 1;

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

        printf("Trying to connect...\n");

        remote.sun_family = AF_UNIX;
        strcpy(remote.sun_path, SOCK_PATH);
        len = strlen(remote.sun_path) + sizeof(remote.sun_family);
        if (connect(s, (struct sockaddr *)&remote, len) == -1) {
            perror("connect");
            exit(1);
        }

        printf("Connected.\n");

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
            printf("PARENT says %s\n",message_buf->message);

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

            printf("Connected.\n");

            // done = 0;
            // do {

            n = recv(s2, message_buf, sizeof(message_buf), 0);
            if (n <= 0) {
                if (n < 0) perror("recv");
            }
            printf("CHILD says %s\n",message_buf->message);

            if (send(s2, child_message, sizeof(child_message), 0) < 0) {
                perror("send");
                done = 1;
            }

            n = recv(s2, str, sizeof(str), 0);
            if (n <= 0) {
                if (n < 0) perror("recv");
            }

            // } while (!done);

            close(s2);
        }
        break;
    }
}