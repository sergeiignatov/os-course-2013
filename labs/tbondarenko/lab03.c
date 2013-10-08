#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[], char *envp[])
{
	(void)execle("/bin/cat", "/bin/cat", "lab2.c" ,0 , envp);
	printf("Error!!!!!");
	exit(-1);
	return 0;
}
