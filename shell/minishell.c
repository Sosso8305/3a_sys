#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>


#define BUFFER 512

// passer a 1 pour obtenir des informations de DEBUG
int DEBUG = 0;

// on stocke le ficheir de destination pour le > dans la variable fdest
char * fdest = NULL;
int append = 0; // 0 FALSE / 1 TRUE
int minishell_pwd(){
	char tmp[BUFFER];
	if(getcwd(tmp, BUFFER) == NULL)
		perror("getcwd");
	else
		fprintf(stdout,"%s\n", tmp);
	return 0;
}

int minishell_cd(char * arg[]){
	if(arg[1] == NULL)
		fprintf(stderr, "usage: cd <directory>\n");
	else
		if (chdir(arg[1]) != 0)
			perror("chdir");
	return 0;
}

ngueur nulle. Si le fichier est une FIFO ou un périphérique terminal, l'attribut O_TRUNC est ignoré. Sinon, le comportement de O_Tint minishell_env(){
	extern char **environ;
	if (environ == NULL){
		fprintf(stderr, "environ: NULL\n");
		return EXIT_FAILURE;
	}

	char ** ptr = environ;
	
	while(*ptr != NULL)
		printf("%s\n", *(ptr++));
	return 0;
}

int minishell_getenv(char *arg[]){
	if (arg[1] == NULL){
		fprintf(stderr, "usage: getenv <environement variable>\n");
		return EXIT_FAILURE;
	}
	else
		if(getenv(arg[1]) == NULL)
			fprintf(stderr,"No such environement variable\n");
		else
			printf("%s:%s\n", arg[1], getenv(arg[1]));
	return 0;
}

int minishell_export(char*arg[]){
	if (arg[1] == NULL){
		fprintf(stderr, "usage: putenv <environment_variable=value\n");
		return EXIT_FAILURE;
	}
	
	if(putenv(arg[1])){
			fprintf(stderr,"putenv: failed to create/modify variable\n");
			return EXIT_FAILURE;
	}
	return 0;
}
/*
 * Lit une commande sur l'entrée standard
 * command : la commande (chemin absolu) a exécuter
 * arg : ses arguments
 */ 
int read_command(char* command, char* arg[]){
	int cpta=1;
	append=0;
	int c;
	char * chaine;
	char tmp[BUFFER];
	// lire la command
	scanf("%s",command);
	
	// exit
	if (strcmp(command,"exit")==0) {
		return -1;
	}

	//lire les arguments
	while((c=getchar())!='\n') {
		chaine=malloc((BUFFER-1) * sizeof(char));
		scanf("%s",chaine);
		if (!strcmp(chaine,">") || !strcmp(chaine,">>")) {
			//lire le fichier de sortie et le stocker dans fdest
			scanf("%s",tmp);
			fdest=malloc(strlen(tmp)*sizeof(char));
			strncpy(fdest,tmp,strlen(tmp)*sizeof(char));
			if (!strcmp(chaine,">>"))
				append = 1;
		}
		
		else{
			arg[cpta++]=chaine;
		}
	}
	arg[cpta]=NULL;
	//on retourne le nombre d'arguments
	return cpta;
}

/*
 * Execute une commande dans un processus fils
 * command : la commande (chemin absolu) a exécuter
 * arg : ses arguments
 */

int run_command(char * command, char * arg[]) {
	pid_t status;
	int fd;
	// change directory
	if (!strcmp(command, "cd")){
		minishell_cd(arg);
		return EXIT_SUCCESS;
	}

	status = fork();

	switch (status) {
		
		case -1:
			perror("Creation processus");
			exit(EXIT_FAILURE);
		
		case 0:
			// fichier de sortie ?
			if(fdest) {
				
				if(append)
					fd=open(fdest, O_WRONLY | O_CREAT | O_APPEND, 0666);
				else
					fd=open(fdest, O_WRONLY | O_CREAT | O_TRUNC, 0666);
				
				if(fd==-1) {
					perror("Erreur : ");
					exit(EXIT_FAILURE);
				}
				dup2(fd, STDOUT_FILENO);
			}
			
			// pwd
			if (!strcmp(command,"pwd"))
				minishell_pwd();
			
			// env
			else if (!strcmp(command, "env"))
				minishell_env();
			
			// getenv
			else if (!strcmp(command, "getenv"))
				minishell_getenv(arg);
            
			// export 
			else if (!strcmp(command,"export"))
				minishell_export(arg);
			
			//utilisation de execv pour exécuter la commande
			else if (execv(command,arg)==-1) {
				perror("Erreur : ");
				exit(EXIT_FAILURE);
			}
			

			if(fdest) {
				close(fd);
			}
			
			exit(EXIT_SUCCESS);
			break;

		default:
			//attente de la fin de la commande
			wait(&status);
			// exit
			if (WIFEXITED(status)) 
				return EXIT_SUCCESS;
			return EXIT_FAILURE;
	}

}

/*
 * Mini interpreteur de commande
 * Lit une commande avec la fonction read_command
 * execute la commande avec run_command
 */

int main(int argc, char ** argv) {
	char command[BUFFER];
	char* arg[BUFFER];
	int nb_args,i;
	if(argc > 1)
		DEBUG=1;
	while(1) {
		// on initialise les variables globales	
		fdest = NULL;
		//on récupère une commande a exécuter
		printf("minishell $ ");
		nb_args=read_command(command, arg);
		arg[0]=command;
		//si la commande correspond a exit, on quitte
		if(nb_args==-1) {
			printf("Exit\n");
			exit(EXIT_SUCCESS);
		}

		if(DEBUG) {
			printf(" ===>commande a exécuter: %s, %d arguments [",command,nb_args);
			for(i=0; i<nb_args; i++)
				printf("%s , ",arg[i]);
			printf("], fdest : %s\n",fdest);
		}
		//on execute la commande
		if(run_command(command,arg)){
			if(DEBUG) printf("===> commande executée avec erreur\n");
		}else{
			if(DEBUG) printf("===> commande executée sans erreur\n");
		}
	}
	return EXIT_SUCCESS;
}


