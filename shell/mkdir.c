#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>


int main(int argc, char ** argv) {
	
	if (argc != 2){
		fprintf(stderr, "usage: %s <name of directory>", argv[0]);
		exit(EXIT_FAILURE);
	}

	if (mkdir(argv[1], 0666)){
		perror("mkdir");
		exit(EXIT_FAILURE);
	}
	return EXIT_SUCCESS;
}
