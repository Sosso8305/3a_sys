#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <utime.h>


int main(int argc, char ** argv){
	int fd;
	if(argc != 2){
		printf("one and only one argument : name of the file\n");
		exit(EXIT_FAILURE);
	}
	if((fd = open(argv[1], O_CREAT|O_RDWR|O_TRUNC)) == -1){
		perror("unable to open file :");
		exit(EXIT_FAILURE);
	}
	if(utime(argv[1], NULL) != 0){
		perror("error setting access and modification time :");
		exit(EXIT_FAILURE);
	}
	if(close(fd) != 0){
		perror("error closing file :");
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
	return 0;
}
