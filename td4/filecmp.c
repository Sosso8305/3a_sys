#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char**argv)
{
	if(argc != 3)
	{
		printf("Usage : %s <path1> <path2>\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	
	FILE * myfile1;
	FILE * myfile2;
	
	if((myfile1 = fopen(argv[1], "r")) == NULL)
	{
		perror("fopen file1");
		exit(EXIT_FAILURE);
	}
	
	if((myfile2 = fopen(argv[2], "r")) == NULL)
	{
		perror("fopen file2");
		exit(EXIT_FAILURE);
	}
	
	char a, b;
	while(1){
		if((a = fgetc(myfile1)) != (b = fgetc(myfile2)))
		{
			printf("NOK\n");
			break;
		}
		else if (a == EOF || b == EOF){
			if (a == EOF && b == EOF)
				printf("OK\n");
			else
				printf("NOK\n");
			break;
		}
	}
			
	fclose(myfile1);
	fclose(myfile2);

	return 0;
}
