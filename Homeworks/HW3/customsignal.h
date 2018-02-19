/***************************************************************
* AUTHOR  : Praveen Gnanasekaran
* DATE    : 02/18/2018
* DESCRITPTION  : This program all definitions for the system call functions
      
* SOURCE FILES  : threads.c
* HEADER FILES  : threads.h, linkedlist.h
****************************************************************/

int glb_var_sig1=0;
int glb_var_sig2=0;

void child1_sigHandler(int signo)
{
  if(signo==SIGUSR1)
  {
    glb_var_sig1=1;
    printf("Thread1:SIG ");
  }
}

void child2_sigHandler(int signo)
{
  if(signo==SIGUSR2)
  {
    glb_var_sig2=1;
    printf("Thread2:SIG ");
  }
}
