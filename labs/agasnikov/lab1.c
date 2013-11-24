#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
	pid_t pid;
	pid = fork();
	int i;
	if (pid == -1)
	{
		printf("Error");
		exit(-1);
	} else
	if (pid == 0)
	{
		printf("идентификатор текущего процесса:%d; идентификатор процесса-родителя для текущего процесса:%d\n" , getpid(),getppid());
		for (i = 0; i < 10; i++)
		{
			printf("Море волнуется:%d\n", i);
		}
	} else
	{
		printf("идентификатор текущего процесса:%d; идентификатор процесса-родителя для текущего процесса:%d\n" , getpid(),pid);
		for (i = 100; i > 90; i--)
		{
			printf("Море волнуется:%d\n", i);
		}
	}
	exit (0);
}
