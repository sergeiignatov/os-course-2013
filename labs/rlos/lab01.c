#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[], char* env[]) {
	printf("--------------------LAB1--------------------\n");
    	pid_t pid;
	pid = fork();
	int i;
	if (pid == -1) { /*Произошла ошибка*/
	   exit(-1);
	} else if (pid == 0) { /*Дочерний процесс*/
 	   printf("Я сын и мой id:%d; А ид моего отца:%d\n" , getpid(),getppid());
	   for (i = 0; i < 10; i++)
	      printf("Сын говорит: %d\n",i);
	   printf("--------------------LAB1ENDchild--------------------\n");
	} else { /*Родительский процесс*/
	   printf("Я отец и мой id:%d; А ид моего сына:%d\n" , getpid(),pid);
	   for (i = 0; i < 100; i++)
	      printf("Отец говорит: %d\n",i);
	   printf("--------------------LAB1ENDparent--------------------\n");
	}
	exit(0);
}
