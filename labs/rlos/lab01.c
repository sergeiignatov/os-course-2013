#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[], char* env[]) {
	printf("--------------------LAB1--------------------\n");
    pid_t pid;
	pid = fork();
	int i;
	if (pid != 0)
		printf("Я отец и мой id:%d; А ид моего сына:%d\n" , getpid(),pid);
	else printf("Я сын и мой id:%d; А ид моего отца:%d\n" , getpid(),getppid());
	for (i = 0; i < 10; i++)
		printf("%d\n",i);
	if (pid != 0)
		printf("--------------------LAB1ENDparent--------------------\n");
	else printf("--------------------LAB1ENDchild--------------------\n");;
	exit(0);
}
