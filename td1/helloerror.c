#include <sys/syscall.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

int main(){
	char string[] = "hello\n";
	int err;
	char * ptrBuff;
	for (int i=0; i<=6; i++){
		err = syscall(SYS_write, i, string, strlen(string));
		ptrBuff = strerror(errno);
		printf("%d: errno=%d, strerror=%s\n", i, errno, ptrBuff);
		if (!err){
	       		perror("syscall");
			printf("Mon perror: %s, syscall, %d\n", ptrBuff, ptrBuff);
		}
	}
}
