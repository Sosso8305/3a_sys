#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void verify_args(int argc, char**argv)
{
	if((argc-1)%2 != 0)	// si le nombre d'arguments n'est pas pair
	{
		printf("Usage : %s name1 mark1 ...", argv[0]);
		exit(EXIT_FAILURE);
	}
}

int main(int argc, char**argv)
{
	verify_args(argc, argv);
	FILE * myfile;
	if((myfile = fopen("note.dat","w")) == NULL)
	{
		perror("fopen");
		return EXIT_FAILURE;
	}

	rewind(myfile);

	for (int i=1;i<argc;i+=2)
	{
		fwrite(argv[i], 1, strlen(argv[i]), myfile);
		fwrite(" ", 1, 2, myfile);
		
	//	int nb_digits = strlen(argv[i+1]);
	//	int number = strtol(argv[i+1], (char**)&argv[i+1][nb_digits], 0);
		fwrite(argv[i+1], 1, strlen(argv[i+1]), myfile);
		fwrite("\n", 1, 1, myfile);
	}
	
	fclose(myfile);	
	return EXIT_SUCCESS;
}
