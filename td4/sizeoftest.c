#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int main(int argc, char*argv[])
{
	if (argc !=2)
		exit(EXIT_FAILURE);
	printf("sizeof(char):%lu",sizeof(char));
	printf("sizeof:%lu strlen:%lu",sizeof(argv[1]),strlen(argv[1]));
	return EXIT_SUCCESS;
}
