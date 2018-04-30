/***************************************************************
* AUTHOR  : Praveen Gnanasekaran
* DATE    : 04/28/2018
* DESCRITPTION  : tests.c
                  
****************************************************************/

#include "/home/praveen/Downloads/cmocka-0.3.2/include/cmocka.h"
#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "../sockets.h"

#define BUFFER_SIZE 1024

int num_char;
int listenfd = 0, connfd = 0;
struct sockaddr_in serv_addr; 

char sendBuff[1025];
time_t ticks; 

void testsocketcreate(void **state) {
  int num_char;
  int listenfd = 0, connfd = 0;
  struct sockaddr_in serv_addr; 

  char sendBuff[1025];
  time_t ticks; 

  listenfd = socket(AF_INET, SOCK_STREAM, 0);

  assert_int_not_equal(-1,listenfd);

}

void testsocketaccept(void **state) {
  listenfd = socket(AF_INET, SOCK_STREAM, 0);
  memset(&serv_addr, '0', sizeof(serv_addr));
  memset(sendBuff, '0', sizeof(sendBuff)); 

  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  serv_addr.sin_port = htons(5000); 

  bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)); 

  listen(listenfd, 10); 
  connfd = accept(listenfd, (struct sockaddr*)NULL, NULL); 
  assert_int_not_equal(0,connfd);
}

void testsocketread(void **state) {
  int num_char;

  num_char = read(connfd, sendBuff, sizeof(sendBuff));
  assert_int_not_equal(0,num_char);
}

void testsocketcompare(void **state) {
  assert_int_not_equal(0,strcmp("TEST",sendBuff));
}


int main(void) {
  const struct UnitTest tests[] = {
      unit_test(testsocketcreate),
      unit_test(testsocketaccept),
      unit_test(testsocketread),
      unit_test(testsocketcompare)
  };

  return run_tests(tests);
}

