/***************************************************************
* AUTHOR	: Praveen Gnanasekaran
* DATE		: 01/31/2018
* DESCRIPTION	: This program does a system call to sort array from user to
					kernel space and then back to user space
		  
* HEADER FILES	: mycronjob.h
****************************************************************/

#include "mycronjob.h"

int main(void)
{
	unsigned long *input_buffer;
	unsigned long *output_buffer;
	int pid, uid;
	char filename[30]="testfile.txt";
	char time_string[40];
	long milliseconds;
	char cwd[1024];

	if (getcwd(cwd, sizeof(cwd)) == NULL)
	   perror("getcwd() error");

	strcat(cwd,"/");
	strcat(cwd,filename);
	
	//CREATING A FILE
	FILE *fp;
	fp = fopen("/home/praveen/Desktop/APES/GITHUB/Advanced-Practical-Embedded-Software-/Homeworks/HW2/p4/testfile.txt", "a");	
	if(fp == NULL){
		printf("Unable to open file\n");
		return 0;
	}

	input_buffer = malloc(BUFFER_SIZE * sizeof(unsigned long));
	output_buffer = malloc(BUFFER_SIZE * sizeof(unsigned long));

	// Use current time as seed for random generator
	srand (time(NULL)); 

	for(int i=0; i< BUFFER_SIZE; i++)
		input_buffer[i] = rand() % BUFFER_SIZE;

	printf("\nGot current date and time\n");
	gettimeofday (&tv, NULL);
	ptm = localtime (&tv.tv_sec);

	/* Format the date and time, down to a single second. */
	strftime (time_string, sizeof (time_string), "%Y-%m-%d %H:%M:%S", ptm);

	/* Compute milliseconds from microseconds. */
	milliseconds = tv.tv_usec / 1000;

	printf("Calling sorter system call\n");
	
	fprintf(fp,"Sorter system call output:\n\nBefore sorting \n");

	for(int i=0; i< BUFFER_SIZE; i++){

		fprintf(fp,"%ld ", (long)input_buffer[i]);
	}

	fprintf(fp,"\n\n\n");

	syscall(333, input_buffer, BUFFER_SIZE, output_buffer );
		
	fprintf(fp,"After sorting\n");

	for(int i=0; i< BUFFER_SIZE; i++){
		fprintf(fp,"%ld ", (long)output_buffer[i]);
	}

	printf("Process ID of the task\n");
	pid = getpid();
	fprintf(fp,"\n\nPROCESS ID of task: %d\n", pid);

	printf("User ID of the task\n");
	uid = getuid();
	fprintf(fp,"USER ID of the task: %d\n", uid);

	fprintf(fp,"Current date and time: %s.%03ld\n", time_string, milliseconds);

	fclose(fp);
	free(input_buffer);
	free(output_buffer);	

	return 0;
}