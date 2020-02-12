#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>


int main(int argc, char ** argv) {
	
	if (argc < 3)
	{
		printf("usage: %s <file1> <file2>\n", argv[0]);
		return EXIT_FAILURE;
	}
	
	FILE * file1;
	FILE * file2;
	
	if ((file1 = fopen(argv[1], "r")) == NULL || (file2 = fopen(argv[2], "r")) == NULL)
	{
		perror("fopen");
		return EXIT_FAILURE;
	}

	int c, d;
	while ((c = fgetc(file1)) != EOF && (d = fgetc(file2)) != EOF)
		if (c!=d)
		{
			printf("DIFFERENT\n");
			fclose(file1);
			fclose(file2);
			return EXIT_SUCCESS;
		}
	printf("OK\n");
	fclose(file1);
	fclose(file2);
	
	return EXIT_SUCCESS;
}
