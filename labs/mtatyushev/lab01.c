#include <stdlib.h>
#include <stdio.h>

int main(int argc, char* argv[], char* env[])
{
    pid_t pid;
	pid = fork();
	if (pid == -1) //обработка ошибки при неудачном выполнении fork()
	{
	   exit(-1);
	} else
		if (pid == 0) //код потомка
		{
			printf("Потомок, имеющий id:%d\n", getpid());
			printf("Родитель потомка, имеющий id:%d\n", getppid());
		} else //код родительского процесса
		{
			printf("Родитель, имеющий id:%d\n", getpid());
			printf("Потомок родителя, имеющий id:%d\n", pid);
		}
	exit(0);
}
