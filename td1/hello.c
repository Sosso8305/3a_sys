#include <sys/syscall.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

int main(){
	char string[] = "hello\n";
	if (!syscall(SYS_write, STDOUT_FILENO, string, strlen(string)))
		perror("syscall");
}
