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

	file_ret=open(cwd,O_CREAT); //if file doesnt exist, create it. open for read/write and append to end of file
	if(file_ret==-1)
		perror("File could not be opened");

	// if(chmod (filename,S_IROTH|S_IWOTH)==-1) //modify file permission to be read/write
	// 	perror("Cannot change file permission");
	return 0;
}