#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(){
	
	// On ouvre un fichier
	FILE * myfile;
	if ((myfile = fopen("myfile.txt", "we")) == NULL)
	{
		perror("fopen");
		exit(EXIT_FAILURE);
	}
	
	printf("[%d] Je suis le père. J'engendre.\n", getpid());

	// On fait un fork
	pid_t status = fork();
	switch(status){
		case -1:
			perror("fork");
			exit(EXIT_FAILURE);
		case 0:
			rewind(myfile);
			printf("[%d] Je viens de naître\n", getpid());
			printf("[%d] J'écris foo à l'offset 3\n", getpid());
			fseek(myfile, 3, SEEK_SET);
			fwrite("foo", sizeof(char), sizeof("foo"), myfile);
			sleep(2);
			break;
		default:
			rewind(myfile);
			printf("[%d] J'ai engendré\n", getpid());
			printf("[%d] J'écris bar à l'offset 3\n", getpid());
			fseek(myfile, 3, SEEK_SET);
			fwrite("bar", sizeof(char), sizeof("bar"), myfile);
			sleep(1);		
			break;
	}
	fclose(myfile);
	return 0;
}
