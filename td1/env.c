#include <stdio.h>
#include <stdlib.h>

extern char **environ;
int main(void){
	char ** ptr = environ;
	while (*ptr!=NULL)
		printf("%s\n", *(ptr++));
	return 0;	
}
