#include "q2.h"

#define NSTRS       3           /* no. of strings  */
#define ADDRESS     "mysocket"  /* addr to connect */

/*
 * Strings we send to the server.
 */
// char *strs[NSTRS] = {
//     "This is the first string from the client.\n",
//     "This is the second string from the client.\n",
//     "This is the third string from the client.\n"
// };

msg_struct actual_msg;

void sock(msg_struct child_message[1],msg_struct parent_message[1],msg_struct* message_buf)
{
    int sockfd;                    // listening FD
    int newsockfd;                 // Client connected FD
    //int addrlen;                   //lenfgth of address
    int num_char;                  //No. of characters red/written
    //  char buffer[256];              //data buffer
    struct sockaddr_in server_addr;//structure containing internet addresss.
    register int i, s, ns, len;
    FILE *fp;
    char c;
    struct sockaddr_un fsaun;
    struct sockaddr_un saun;
    int fromlen;

    strcpy(actual_msg.message,"SOMEMEMSSAGE");
    actual_msg.led_status=1;

    switch(fork()) 
    {
    case -1:
            printf("fork Error:%s\n",strerror(errno));
            break;

    case 0://child process - client

        /*
         * Get a socket to work with.  This socket will
         * be in the UNIX domain, and will be a
         * stream socket.
         */
        if ((s = socket(AF_UNIX, SOCK_STREAM, 0)) < 0) {
            perror("client: socket");
            exit(1);
        }

        /*
         * Create the address we will be connecting to.
         */
        saun.sun_family = AF_UNIX;
        strcpy(saun.sun_path, ADDRESS);

        /*
         * Try to connect to the address.  For this to
         * succeed, the server must already have bound
         * this address, and must have issued a listen()
         * request.
         *
         * The third argument indicates the "length" of
         * the structure, not just the length of the
         * socket name.
         */
        len = sizeof(saun.sun_family) + strlen(saun.sun_path);

        if (connect(s, &saun, len) < 0) {
            perror("client: connect");
            exit(1);
        }

        /*
         * We'll use stdio for reading
         * the socket.
         */
        fp = fdopen(s, "r");

        /*
         * First we read some strings from the server
         * and print them out.
         */
            while ((c = fgetc(fp)) != EOF) {
                putchar(c);

                // if (c == '\n')
                //     break;
            }

        /*
         * Now we send some strings to the server.
         */
        // for (i = 0; i < NSTRS; i++)
            send(s, &actual_msg, sizeof(actual_msg), 0);

        /*
         * We can simply use close() to terminate the
         * connection, since we're done with both sides.
         */
        close(s);

        break;

    default://parent - server

        /*
         * Get a socket to work with.  This socket will
         * be in the UNIX domain, and will be a
         * stream socket.
         */
        if ((s = socket(AF_UNIX, SOCK_STREAM, 0)) < 0) {
            perror("server: socket");
            exit(1);
        }

        /*
         * Create the address we will be binding to.
         */
        saun.sun_family = AF_UNIX;
        strcpy(saun.sun_path, ADDRESS);

        /*
         * Try to bind the address to the socket.  We
         * unlink the name first so that the bind won't
         * fail.
         *
         * The third argument indicates the "length" of
         * the structure, not just the length of the
         * socket name.
         */
        unlink(ADDRESS);
        len = sizeof(saun.sun_family) + strlen(saun.sun_path);

        if (bind(s, &saun, len) < 0) {
            perror("server: bind");
            exit(1);
        }

        /*
         * Listen on the socket.
         */
        if (listen(s, 5) < 0) {
            perror("server: listen");
            exit(1);
        }

        /*
         * Accept connections.  When we accept one, ns
         * will be connected to the client.  fsaun will
         * contain the address of the client.
         */
        if ((ns = accept(s, &fsaun, &fromlen)) < 0) {
            perror("server: accept");
            exit(1);
        }

        /*
         * We'll use stdio for reading the socket.
         */
        fp = fdopen(ns, "r");

        /*
         * First we send some strings to the client.
         */
        // for (i = 0; i < NSTRS; i++)
            send(ns, &actual_msg, sizeof(actual_msg), 0);

        /*
         * Then we read some strings from the client and
         * print them out.
         */
            while ((c = fgetc(fp)) != EOF) {
                putchar(c);

                // if (c == '\n')
                //     break;
            }

        /*
         * We can simply use close() to terminate the
         * connection, since we're done with both sides.
         */
        close(s);

        break;
    }
}