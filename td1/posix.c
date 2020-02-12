// EXERCICE 1
#include <stdio.h>

int main(){
	
	#ifdef _POSIX_SOURCE
	printf("_POSIX_SOURCE=%d\n",_POSIX_SOURCE);
	#endif
	#ifdef _SVID_SOURCE
	printf("_SVID_SOURCE=%d\n",_SVID_SOURCE);
	#endif
	#ifdef _GNU_SOURCE
	printf("_GNU_SOURCE=%d\n",_GNU_SOURCE);
	#endif
	#ifdef _ISO99_SOURCE
	printf("_ISO99_SOURCE=%d\n",_ISO99_SOURCE);
	#endif
	#ifdef _POSIX_C_SOURCE
	printf("_POSIX_C_SOURCE=%d\n",_POSIX_C_SOURCE);
	#endif
	#ifdef _XOPEN_SOURCE
	printf("_POSIX_C_SOURCE=%d\n",_POSIX_C_SOURCE);
	#endif
	#ifdef _XOPEN_SOURCE_EXTENDED
	printf("_XOPEN_SOURCE_EXTENDED=%d\n",_XOPEN_SOURCE_EXTENDED);
	#endif
	#ifdef _BSD_SOURCE
	printf("_BSD_SOURCE=%d\n",_BSD_SOURCE);
	#endif
	#ifdef __STRICT_ANSI
	printf("__STRICT_ANSI=%d\n",__STRICT_ANSI);
	#endif
	#ifdef __LARGEFILE64_SOURCE
	printf("__LARGEFILE64_SOURCE=%d\n",__LARGEFILE64_SOURCE);
	#endif

	if (_POSIX_SOURCE == 2008)
		printf("Code de 2008 inclus !\n");
	else
		printf("Code par défaut\n");
	#if _POSIX_SOURCE==200112
		printf("Code de 2008 inclu par un #if\n");
	#endif
}
