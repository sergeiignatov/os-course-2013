#include <stdlib.h>
#include <stdio.h>

int main(int argc, char* argv[], char* env[])
{
	int i;
	printf("argc = %d\n", argc);
	for(i = 0; i < argc; i++)
		printf("argv[%d] = %s\n", i, argv[i]);
	i = 0;
	for(i = 0; env[i] != NULL; i++)
		printf("env[%d] = %s\n", i, env[i]);
	}
	exit(0);
}
