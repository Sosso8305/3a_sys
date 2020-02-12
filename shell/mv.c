#include<fcntl.h>
#include<stdio.h>
#include<unistd.h>
#include <stdlib.h>
#include<sys/stat.h>

int main(int argc, char **argv){

	if (argc != 3){
		fprintf(stderr,"usage : %s <src> <dest>", argv[0]);
		exit(EXIT_FAILURE);
	}

	if (access(argv[1],F_OK)){
		perror("access source");
		exit(EXIT_FAILURE);
	}
	
	if(rename(argv[1], argv[2])){
		perror("rename");
		exit(EXIT_FAILURE);
	}

	if(unlink(argv[1]) == -1){
		perror("unlink");
		exit(EXIT_FAILURE);
	}
	
	return 0;
}
