#include "q2.h"

void sock()
{
   int sockfd;                    // listening FD
    int newsockfd;                 // Client connected FD
    //int addrlen;                   //lenfgth of address
    int num_char;                  //No. of characters red/written
    //  char buffer[256];              //data buffer
    struct sockaddr_in server_addr;//structure containing internet addresss.

    switch(fork()) {
    case -1:
            printf("fork Error:%s\n",strerror(errno));
            return -1;

    case 0://child process - client
            printf("Entering Child-client, PID:%d\n",getpid());

/****create socket********/
            sockfd = socket(
                    AF_INET, // com domain - IPv4
                    SOCK_STREAM, //com type - TCP
                    0); //protocol
            if(sockfd < 0) {printf("socket Error:%s\n",strerror(errno)); return -1;}
/*****clear and initialize the server address structure*****/
            memset(&server_addr,'0',sizeof(server_addr));
            server_addr.sin_family = AF_INET;
            server_addr.sin_port = htons(PORT);

/*convert IP addr from text to binary*/
            ret = inet_pton(AF_INET,"127.0.0.1",&server_addr.sin_addr);
            if(ret<0) {printf("inet_pton Error:%s\n",strerror(errno)); return -1;}

/****connect socket to the address specified in server_addr******/
            ret = connect(sockfd,(struct sockaddr*)&server_addr,sizeof(server_addr));
            if(ret<0) {printf("connect Error:%s\n",strerror(errno)); return -1;}

/******write to socket******/
            num_char =  send(sockfd,child_message,sizeof(child_message),0 );
            printf("message sent from child\n");
/*****read from socket*****/
            num_char = read(sockfd,(char*)message_buf,sizeof(message_buf));
            printf("read in child:%s;led_status:%d\n",
                   ((msg_struct*)message_buf)->message,
                   ((msg_struct*)message_buf)->led_status);

            break;

    default://parent - server
            printf("Parent Process-server, PID:%d\n",getpid());
            int opt = 1;
/****Create a new socket*******/
            sockfd = socket(
                    AF_INET, // com domain - IPv4
                    SOCK_STREAM, //com type - TCP
                    0);   //protocol
            if(sockfd < 0) {printf("fork Error:%s\n",strerror(errno)); return -1;}
/*****set options for the socket***********/
            ret = setsockopt(sockfd,
                             SOL_SOCKET,          //Socket Level Protocol
                             SO_REUSEADDR|SO_REUSEPORT,
                             &opt, //option is enabled
                             sizeof(opt) );

            if(ret==-1) {printf("setsockopt Error:%s\n",strerror(errno)); return -1;}
/***initialize the address structure ****/
            bzero((char*)&server_addr, sizeof(server_addr));//sets all val to 0
            server_addr.sin_family=AF_INET;
            server_addr.sin_addr.s_addr=INADDR_ANY;
            server_addr.sin_port=htons(PORT);

/***bind socket to the adress and the port */
            ret = bind(sockfd,
                       (struct sockaddr*)&server_addr,
                       sizeof(server_addr));
            if(ret == -1) {printf("bind Error:%s\n",strerror(errno)); return -1;}
/**listen on socket for connections**/
            ret = listen(sockfd,5);
            if(ret == -1) {printf("listen Error:%s\n",strerror(errno)); return -1;}
/****block until the client connects to the server and gets its address*****/
            struct sockaddr_in client_addr;
            socklen_t addrlen = sizeof(client_addr); //size of address of client
            newsockfd = accept(sockfd,
                               (struct sockaddr*)&client_addr,
                               (socklen_t*)&addrlen);
            if(newsockfd<0) {printf("accept Error:%s\n",strerror(errno)); return -1;}

/*****beyond this, execution happens only after client is connected******/

/****read from the client and write to it*******/
            bzero(message_buf,sizeof(message_buf));

            num_char = read(newsockfd,(char*)message_buf,sizeof(message_buf));
            if(num_char<0) {printf("read Error:%s\n",strerror(errno)); return -1;}
            printf("read in parent:%s;led_status:%d\n",
                   ((msg_struct*)message_buf)->message,
                   ((msg_struct*)message_buf)->led_status);

            num_char = write(newsockfd,parent_message,sizeof(parent_message));
            if(num_char<0) {printf("write Error:%s\n",strerror(errno)); return -1;}
            else printf("Message sent from parent\n");

    }
}