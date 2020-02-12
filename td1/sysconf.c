#include <stdio.h>
#include <unistd.h>

int main()
{
	int j;
	j = sysconf(_SC_VERSION);
	printf("_SC_VERSION=%i\n", j);
}
