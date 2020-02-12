#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main (void){
	pid_t status;
	printf ("[%d] Je vais engrendrer\n", getpid());
	status = fork();
	switch(status){
		case -1:
			perror("Création processus");
			exit(EXIT_FAILURE);
		case 0:
			printf("[%d] Je viens de naitre\n", getpid());
			printf("[%d] Mon père est %d\n", getpid(), getppid());
			sleep(500);
			break;
		default:
			printf("[%d] J'ai engendré\n", getpid());
			printf("[%d] Mon fils est %d\n", getpid(), status);
	}
	printf("[%d] Je termine\n", getpid());
	return 0;
}
