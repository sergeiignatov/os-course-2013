#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[], char* env[]) 
{
	execl(argv[1], argv[1], argv[0], 0); 
	printf("Error on program start\n"); //сюда попадаем только при возникновении ошибки
	exit(-1);
}