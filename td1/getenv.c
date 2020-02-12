#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv){
	int ind = argc-1;
	if (ind == 0){
		printf("Give at least one argument\n");
		return EXIT_FAILURE;
	}
	else{
		while (ind > 0){
			printf("%s:%s\n", argv[ind], getenv(argv[ind]));
			ind--;
		}
	}
	return EXIT_SUCCESS;
}
