#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <errno.h>
#include <string.h>


void print_stat(const char *ref, struct stat *statut) {
    
    struct passwd *pw;
    struct group *gr;
    char type;
    #define LTEMPS 32
    #define LINKN 32
    char pws[9], grs[9], temps[LTEMPS], linkn[LINKN];
    type = '?';
    
    if      (S_ISREG(statut->st_mode )) type = '-';
    else if (S_ISLNK(statut->st_mode )) type = 'l';
    else if (S_ISDIR(statut->st_mode )) type = 'd';
    else if (S_ISCHR(statut->st_mode )) type = 'c';
    else if (S_ISBLK(statut->st_mode )) type = 'b';
    else if (S_ISFIFO(statut->st_mode)) type = 'p';
    
    strftime(temps,LTEMPS,"%a %e %h %Y %H:%M:%S",localtime(&(statut->st_mtime)));
    
    pw = getpwuid(statut->st_uid);
    
    if (pw!=NULL) 
        strcpy(pws,pw->pw_name);
    else 
        sprintf(pws,"%8d",(int)statut->st_uid);
    
    gr = getgrgid(statut->st_gid);
    
    if (gr!=NULL) 
        strcpy(grs,gr->gr_name);
    else 
        sprintf(grs,"%8d",(int)statut->st_gid);


    printf("%c%c%c%c%c%c%c%c%c%c %2d %8s %8s %9d %s %s", type,
    statut->st_mode&S_IRUSR ?'r':'-',
    statut->st_mode&S_IWUSR ?'w':'-',
    statut->st_mode&S_IXUSR ?'x':'-',
    statut->st_mode&S_IRGRP ?'r':'-',
    statut->st_mode&S_IWGRP ?'w':'-',
    statut->st_mode&S_IXGRP ?'x':'-',
    statut->st_mode&S_IROTH ?'r':'-',
    statut->st_mode&S_IWOTH ?'w':'-',
    statut->st_mode&S_IXOTH ?'x':'-',
    (int)statut->st_nlink, pws,grs, (int)statut->st_size,temps,ref );
    
    if (S_ISLNK(statut->st_mode )){
        if(readlink(ref, linkn, LINKN) == -1) perror("error reading link");;
        printf(" -> %s",linkn);
    }
    printf("\n");
}

void lookup(const char * name) {
    struct stat statut;
    DIR * dirp; 
    struct dirent * dp;
    char  buf [32];
    if ((dirp = opendir(name)) == NULL) 
        perror(name); 
    while (dp = readdir(dirp)) {
	    if (dp->d_name[0] != '.'){
		    if ( lstat(dp->d_name,&statut) == 1 ) {
		        fprintf(stderr,"impossible d'obtenir le statut de %s\n", dp->d_name);
		        continue; 
		    }
		    else{ 
		        print_stat(dp->d_name, &statut);
            }
	    }
    }
    if (errno != 0) 
        perror("error reading directory");
    else 
        closedir(dirp);    
}

int main(int argc,const char *argv[]) {
    struct stat statut;
    int i;
    if (argc<2) {
        lookup(".");
    }
    else {
        if (chdir(argv[1])) perror("error changing directory");
        lookup(".");
    }
    exit(EXIT_SUCCESS);
}
