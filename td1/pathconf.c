#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#define PATH_STR_LEN 64
#define PARAM_STR_LEN 64
#define NB_PARAM 30
// #define getVarName(myVar) #var

void pr_pathconf(char *path, int name, char* message)
{
	int value;
	value = pathconf(path, name);
	if (value == -1)
	{
		char* errmsg = strerror(errno);
		fprintf(stderr, errmsg, strlen(errmsg)+1);
		exit(EXIT_FAILURE);
	}		
	printf("%s:%d", message,value);
}

int main(int argc, char **argv)
{
	if (argc != 3)
	{
		printf("Usage: %s path parameter\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	if (strlen(argv[2]) > PARAM_STR_LEN || strlen(argv[1]) > PATH_STR_LEN)
	{
		printf("Argument length can't exceed %d characters\n", PATH_STR_LEN);
		exit(EXIT_FAILURE);
	}
	
	// Tableau contenant les noms des paramètres
	char strparam[PARAM_STR_LEN][30];
	int param[30];
	
	// On recopie chaque paramètre 1 par 1
	strcpy(strparam[0], "_PC_LINK_MAX");
	param[0] = _PC_LINK_MAX;
	strcpy(strparam[1], "_PC_MAX_CANON");
	param[1] = _PC_MAX_CANON;
	// etc...
	
	for (int i=0; i<30; i++)
		if(!strcmp(strparam[i], argv[2])){
			pr_pathconf(argv[1], param[i], argv[2]);
			return 0;
		}	
	
	printf("No such paramater");
	
	return 0;
}
