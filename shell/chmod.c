#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>


int main(int argc, char ** argv) {
	
	if(argc != 3){
		fprintf(stderr,"usage: %s <rights> <file>", argv[0]);
		exit(EXIT_FAILURE);
	}

	if(access(argv[2], F_OK))
	{
		perror("access file");
		exit(EXIT_FAILURE);
	}
	FILE * fd;
	
	if((fd = open(argv[2], O_WRONLY)) == NULL ){
		perror("open");
		exit(EXIT_FAILURE);
	}
	
	// A IMPLEMENTER	

	close(fd);
	return EXIT_SUCCESS;
}
