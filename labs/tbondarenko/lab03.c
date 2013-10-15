#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[], char *envp[])
{
	(void)execle("/home/jsmith/tanya/lab2", "/home/jsmith/tanya/lab2", 0 , envp);
	printf("Error!!!!!");
	exit(-1);
	
}