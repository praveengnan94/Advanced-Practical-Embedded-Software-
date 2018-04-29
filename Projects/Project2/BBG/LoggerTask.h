#include <errno.h>
#include <mqueue.h>
#include <pthread.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "msgque.h"

#define UV_ALIVE 1
#define PR_ALIVE 4