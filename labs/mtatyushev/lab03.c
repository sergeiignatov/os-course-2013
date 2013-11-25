#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char* argv[], char* env[])
{
	if(execvp("./lab2", argv) = -1)
	{
		printf("Ошибка, не удалось запустить 2 лабу.\n");
    }
	exit(-1);
}
