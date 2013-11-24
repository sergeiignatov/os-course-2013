#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[], char* env[]) 
{
	printf("количество аргументов командной строки:%d\n" , argc);
	execl("/home/sandron/INNA/Sandron/lab2.c","/home/sandron/INNA/Sandron/lab2.c", NULL);
	printf("Ошибочка вышла!");
	exit(-1);
}
