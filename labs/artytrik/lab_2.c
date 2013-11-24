#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[], char *envp[])
{
    int i = 0;
    while(i != argc )
    {
		printf("Вывод значений аргументов в функции main\n");
        printf("%s\n" , argv[i]);
        i++;
    }
	
    i = 0;
    while( envp[i] != NULL )
	{
        printf("%s\n" , envp[i]);
        i++;
    }
    exit(0);
}