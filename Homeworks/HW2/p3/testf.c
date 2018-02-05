/***************************************************************
* AUTHOR	: Praveen Gnanasekaran
* DATE		: 01/29/2018
* DESCRIPTION	: This program does a system call to sort array from user to
					kernel space and then back to user space
		  
* HEADER FILES	: testf.h
****************************************************************/

#include "testf.h"

int main()
{
	unsigned long *input_buffer;
	unsigned long *output_buffer;
	unsigned long i,j,k;

	// Execute system call n number of times
	// for (i =0; i< TOTAL_CALLS; i++)
	{
		input_buffer = malloc(BUFFER_DEPTH * sizeof(unsigned long));
		output_buffer = malloc(BUFFER_DEPTH * sizeof(unsigned long));

		// Use current time as seed for random generator
		srand (time(NULL)); 

		for(j=0; j< BUFFER_DEPTH; j++)
			input_buffer[j] = rand() % BUFFER_DEPTH;

		printf("\nBefore syscall \n");

		syscall(333, input_buffer, BUFFER_DEPTH, output_buffer );

		printf("\nBefore sorting \n");
		for(k=0; k< BUFFER_DEPTH; k++)
			printf("%ld : %ld\n", (long)k, (long)input_buffer[k]);
		
		printf("\nAfter sorting \n");
		for(k=0; k< BUFFER_DEPTH; k++)
			printf("%ld : %ld\n", (long)k, (long)output_buffer[k]);

		free(input_buffer);
		free(output_buffer);
	}
	
	
	return 0;
}