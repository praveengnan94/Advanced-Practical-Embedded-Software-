#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/stat.h> 
#include <fcntl.h> //file system calls
#include <string.h>

int main(int argc, char const *argv[])
{
	int file_ret; //return type of file system calls
	char filename[20]="testfile.txt";
	char cwd[1024];
	if (getcwd(cwd, sizeof(cwd)) == NULL)
	   perror("getcwd() error");

	strcat(cwd,"/");
	strcat(cwd,filename);
	printf("Some interesting output %s\n",cwd);

	file_ret=open(cwd,O_CREAT); //if file doesnt exist, create it

	if(file_ret==-1)
		perror("File could not be opened");
	if(close(file_ret)==-1)
		perror("File could not be closed");

	if(chmod (filename,S_IROTH|S_IWOTH)==-1) //modify file permission to be read/write
		perror("Cannot change file permission");

	file_ret=open(cwd,O_WRONLY); //open file for writing

	if(write(file_ret,"a",sizeof(char))==-1) //write a character to the file
		perror("Cannot write a character to the file");
	if(close(file_ret)==-1)
		perror("File could not be closed");

	file_ret=open(cwd,O_APPEND|O_RDWR); //open file in append mode

	if(file_ret==-1)
		perror("File could not be opened");
	char *dynamic_mem= (char*)malloc(200);

	printf("Enter a string to write to the file\n");

	scanf("%s",dynamic_mem);

	if(write(file_ret,dynamic_mem,strlen(dynamic_mem))==-1)
		perror("Cannot write string to the file");

	
	file_ret=open(cwd,O_RDONLY);
	if(file_ret==-1)
		perror("File could not be opened");

	char read_file[200];
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

	// file_ret=open(cwd,O_RDONLY);
	FILE *fp = fopen(cwd,"r+");
	if(file_ret==-1)
		perror("File could not be opened");

	printf("single character %c\n",getc(fp));

	printf("string of characters %s\n",gets(fp));

	if(fclose(fp)==-1)
		perror("File could not be closed");

	free(dynamic_mem); //free the allocated memory
	
	return 0;
}
 