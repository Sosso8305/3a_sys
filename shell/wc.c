#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>


int main(int argc, char ** argv) {
	if (argc < 2)
	{
		printf("usage: %s <text file>\n", argv[0]);
		return EXIT_FAILURE;
	}
	
	FILE * myfile;
	if ((myfile = fopen(argv[1], "r")) == NULL)
	{
		perror("fopen");
		return EXIT_FAILURE;
	}
	
	char c;
	int count = 0;
	
	while ((c = fgetc(myfile)) != EOF)
		if(c == '\n')
		       count++;
	
	printf("%d\n", count);

	return EXIT_SUCCESS;	
}
