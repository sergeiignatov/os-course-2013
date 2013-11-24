#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[], char* env[]) 
{
	printf("количество аргументов командной строки:%d\n" , argc);
	int i=0;
	printf("массив указателей собственно на аргументы:");
	for (i;i<argc;i++)
		printf("%s\n" , argv[i]);
	i = 0;
	printf("массив указателей на цепочки символов из окружающей среды:");
	while( env[i] != NULL )
	{
		printf("%s\n" , env[ i ]);
		i++;
	}
	exit(0);
}
