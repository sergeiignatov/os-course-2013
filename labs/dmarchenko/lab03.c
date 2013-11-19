#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[], char *envp[])
{
	printf("Будет выполнена программа %s\n", argv[1]);
	printf("Argument count: %d\n\n",argc);
	execle(argv[1], argv[1], argv[0], 0, envp);
	printf("Ошибка!!! \n");
	exit(-1);
}