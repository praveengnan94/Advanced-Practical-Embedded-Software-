#include "uartServer.h"

void uartinit()
{

   if ((uartfile = open("/dev/ttyO1", O_RDWR)) <0){       // | O_NOCTTY | O_NDELAY))<0){
      perror("UART: Failed to open the file.\n");
      exit(1);
   }

   printf("UART open success\n");
   tcgetattr(uartfile, &uartoptions);            //Sets the parameters associated with file
   if (cfsetispeed(&uartoptions, B9600) < 0)
   {
      printf("UART not success\n");       
      exit(1);
   }

   // Set up the communications options:
   //   9600 baud, 8-bit, enable receiver, no modem control lines
    uartoptions.c_iflag = 0;
    uartoptions.c_oflag = 0;
    uartoptions.c_lflag = 0;
    uartoptions.c_cc[VMIN] = 45;//works for 1
    uartoptions.c_cc[VTIME] = 0;
    tcsetattr(uartfile, TCSANOW, &uartoptions); //Set newly-modified attributes
}

int uartWrite(uartstructre *uartstruct)
{
  int count;
  unsigned char* transmit = (unsigned char*)malloc(sizeof(uartstruct));

  if ((count = write(uartfile, &uartstruct,sizeof(uartstruct)))<0){        //send the string
      perror("Failed to write to the output\n");
      return -1;
   }
   printf("UART write complete\n");
   return 1;

}

int uartRead(uartstructre *uartstruct)
{
  int count;

  if ((count = read(uartfile, (void*)uartstruct, 16))<0){   //receive the data
      perror("Failed to read from the input\n");
     return -1;
   }
   if (count==0)
   {
      printf("There was no data available to read!\n");
      return -1;
   }
   else {
      // printf("The following UART count was read [%d]\n",count);
      return 1;
   }
}
