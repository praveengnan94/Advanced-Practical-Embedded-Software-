// #include "q2.h"
#include "q2sock.c"

int main(){

    /*linux has Half duplex setting, thus file_descriptor[0] is always used for reading,file_descriptor[1] always used for writing*/
    msg_struct child_message[1];
    strcpy(child_message->message,"Hello from Child");
    child_message->led_status = 0;

    msg_struct parent_message[1];
    strcpy(parent_message->message,"Hello from Parent");
    parent_message->led_status = 1;

    msg_struct* message_buf = (msg_struct*)malloc(sizeof(msg_struct));
    if(message_buf==NULL) {printf("malloc Error: %s\n", strerror(errno)); return -1;}


    sock(child_message,parent_message,message_buf);

    // free(message_buf);
    return 0;
}