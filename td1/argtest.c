#include <stdio.h>

int main(int argc, char**argv){
	int ind = argc-1;
	while (ind >= 0){
		printf("%d:%s\n", ind, argv[ind]);
		ind--;
	}
}

