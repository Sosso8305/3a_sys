#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>


int main(int argc, char *argv[]){

	if(argc!= 3){
		fprintf(stderr, "usage : %s <source> <dest>", argv[0]);
    		exit(EXIT_FAILURE);
  	}

	if (access(argv[1], F_OK)){
		perror("access source file");
		exit(EXIT_FAILURE);
	}

	if (symlink(argv[1], argv[2])){
		perror("symlink");
		exit(EXIT_FAILURE);
	}
  
	return 0;
}
