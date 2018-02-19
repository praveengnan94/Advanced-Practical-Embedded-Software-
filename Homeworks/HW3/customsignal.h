
int glb_var_sig1=0;
int glb_var_sig2=0;

void child1_sigHandler(int signo)
{
  if(signo==SIGUSR1)
  {
    glb_var_sig1=1;
    printf("Thread1:SIGU");
  }
}

void child2_sigHandler(int signo)
{
  if(signo==SIGUSR2)
  {
    glb_var_sig2=1;
    printf("Thread2:SIGU");
  }
}
