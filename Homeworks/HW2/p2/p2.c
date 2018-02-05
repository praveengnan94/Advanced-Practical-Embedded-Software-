
/***************************************************************
* AUTHOR	: Praveen Gnanasekaran
* DATE		: 01/29/2018
* DESCRITPTION	: This program creates a new file, modifies its contents and 
					flushes the file outputs while creating and freeing 
					dynamic memory
		  
* HEADER FILES	: p2.h
****************************************************************/

#include "p2.h"

int main(int argc, char const *argv[])
{
	int file_ret; //return type of file system calls
	char filename[20]="testfile.txt";
	char cwd[1024];
	if (getcwd(cwd, sizeof(cwd)) == NULL)
	   perror("getcwd() error");

	strcat(cwd,"/");
	strcat(cwd,filename);
	printf("Some interesting output!\n");

	//CREATING A FILE
	file_ret=open(cwd,O_CREAT); //if file doesnt exist, create it

	if(file_ret==-1)
		perror("File could not be opened");
	if(close(file_ret)==-1)
		perror("File could not be closed");
	printf("file created\n");

	//modify file permission to be read/write
	if(chmod (filename,S_IROTH|S_IWOTH)==-1) 
		perror("Cannot change file permission");

	printf("FILE permission modified\n");

	file_ret=open(cwd,O_WRONLY); //open file for writing
	printf("file opened for writing\n" );

	if(write(file_ret,"a",sizeof(char))==-1) //write a character to the file
		perror("Cannot write a character to the file");
	if(close(file_ret)==-1)
		perror("File could not be closed");
	printf("Writing the character \'a\' to the file\n");

	file_ret=open(cwd,O_APPEND|O_RDWR); //open file in append mode

	if(file_ret==-1)
		perror("File could not be opened");
	char *dynamic_mem= (char*)malloc(MAX_SIZE);
	printf("Dynamic memory allocated\n");

	printf("Enter a string to write to the file\n");

	scanf("%s",dynamic_mem);

	if(write(file_ret,dynamic_mem,strlen(dynamic_mem))==-1)
		perror("Cannot write string to the file");

	
	file_ret=open(cwd,O_RDONLY);
	if(file_ret==-1)
		perror("File could not be opened");

	char read_file[MAX_SIZE];
	int ret_val;

	printf("Flushing file output\n");

	while(ret_val=read(file_ret,read_file,1)){
		if(ret_val==-1)
			perror("Cannot read contents from file");				
		printf("%c",*read_file);
	}

	printf("\n");
	
	if(close(file_ret)==-1)
		perror("File could not be closed");

	printf("opening file for reading\n");
	FILE *fp = fopen(cwd,"r+");
	if(file_ret==-1)
		perror("File could not be opened");

	printf("single character %c\n",getc(fp));

	fp = fopen(cwd,"r+");
	//GET string of characters
	fgets(read_file,MAX_SIZE,fp);
	printf("string of characters: ");
	puts(read_file);

	if(fclose(fp)==-1)
		perror("File could not be closed");

	printf("Closing file and freeing dynamic memory\n");

	free(dynamic_mem); //free the allocated memory
	
	return 0;
}
 