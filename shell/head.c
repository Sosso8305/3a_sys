#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>

int main (int argc, char* argv[]){
	int i;
	int j=1;
	if (argc < 2){
		printf("usage: %s <file1> <file2> ...\n", argv[0]);
		return EXIT_FAILURE;
	}
	
	for (i=1; i<argc; i++)
	{
		FILE * myfile;
		if ((myfile = fopen(argv[i], "r")) == NULL)
		{
			perror("fopen");
			return EXIT_FAILURE;
		}
		else{
			char c;
			while ((c = fgetc(myfile)) != EOF){
				printf("%c", c);
				if (c == '\n')
					j++;
				if (j == 10)
					break;
			}
		}
		fclose(myfile);
	}	
	return EXIT_SUCCESS;
}
