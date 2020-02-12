#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

#define BUFF 1024


int main(int argc, char *argv[]){

	if(argc!= 3){
		fprintf(stderr, "usage : %s <source> <dest>", argv[0]);
    		exit(EXIT_FAILURE);
    		return 0;
  	}

	int fd1, fd2, nb_read;
	char buf[BUFF];

	if((fd1 = open(argv[1], O_RDONLY)) == -1){
    		perror("open source");
		exit(EXIT_FAILURE);
  	}
  
	if((fd2 = open(argv[2], O_WRONLY | O_CREAT, 0666)) == -1){
   		perror("open dest");
		exit(EXIT_FAILURE);
  	}
  
	while((nb_read = read(fd1, buf, BUFF)) > 0){

		if(write(fd2, buf, nb_read) == -1){
      			perror("write");
	      		exit(EXIT_FAILURE);
    		}
 	}
	if(nb_read == -1){
    		perror("error reading from file");
	    	exit(EXIT_FAILURE);
	}
	if(close(fd1) == -1){
    		perror("error closing source file");
	    	exit(EXIT_FAILURE);
	}
  	if(close(fd2) == -1){
    		perror("error closing destination file :");
		exit(EXIT_FAILURE);
	}
	
	return 0;
}
