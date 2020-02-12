#include <stdio.h>
#include <stdlib.h>
#include <pwd.h>
#include <string.h>

static void info_user(char * username){
	struct passwd * user = getpwnam(username);

	if (user == NULL)
		printf("Unknown user\n");
	
	else{
		printf("Username: %s\n", user->pw_name);
		printf("Password: %s\n", user->pw_passwd);
		printf("UID: %d\n", (int)user->pw_uid);
		printf("GID: %d\n", (int)user->pw_gid);
		printf("Real name: %s\n", user->pw_gecos);
		printf("Directory: %s\n", user->pw_dir);
		printf("Shell: %s\n", user->pw_shell);
	}
}

// version qui utilise les fcts de manipulation de fichiers
static void info_all_users(void){
	FILE * myfile = fopen("/etc/passwd", "r");
	if(myfile == NULL){
		printf("File doesn't exist");
		exit(EXIT_FAILURE);
	}
	rewind(myfile); // utile ??
	while(1){
		char username[32];
		int i = 0;
		if ((username[i++]=fgetc(myfile)) == EOF)
			break;
		while(1){
			if((username[i++]=fgetc(myfile)) == ':')
			{
				username[i-1] = '\0';
				printf("\nUSER %s\n\n", username);
				info_user(username);
				while(fgetc(myfile) != '\n');	
				break;
			}
		}	
	}
	fclose(myfile);
}

// Version qui utilise les commandes wc, grep, cat et cut
// static void info_all_users_system(void)

int main (int argc, char *argv[]){
	if (argc != 2){
		printf("Usage: %s username\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	if (!strcmp("-a", argv[1]))
		info_all_users();
	
	else	
		info_user(argv[1]);
	
	return 0;
}
