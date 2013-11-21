#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// обработайте случай ошибки при вызове fork() и будет отлично
int main()
{
	pid_t pid;
	pid = fork();
	int i;
	if (pid == 0)
	{
		printf("id сына: %d\n", getpid());
		printf("id отца: %d\n", getppid());
		for (i = 0; i < 10; i++)
		{
			printf("%d\n", i*2);
		}
		
		return 0;
	}
	printf("id отца: %d\n", getpid());
	printf("id сына: %d\n", pid);
	for (i = 100; i > 90; i--)
	{
		printf("%d\n", i/2);
	}
	return 0;
	
}
