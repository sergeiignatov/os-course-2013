#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char* argv[], char* env[])
{
	int fd_p[2], fd_c[2], pid_dan;
	size_t size;
	char* str[] = {"Luck!", "I am your father!", "Nooo!", "You lie!"};
	int i;
	int flag = 0;
	char resstr[64];
	
	if (pipe(fd_p) < 0)
	{
		printf("Can't create pipe\n");
		exit(-1);
	}
	
	if (pipe(fd_c) < 0)
	{
		printf("Can't create pipe\n");
		exit(-1);
	}
	
	pid_dan = fork();
	
	if (pid_dan < 0)
	{
		printf("Can't create fork\n");
		exit(-1);
	}
	
	if (pid_dan > 0)
	{
		i = 0;
		close(fd_c[0]);
		close(fd_p[1]);
		while (flag == 0)
		{
			size = write(fd_c[1], str, 64);
			while (size = read(fd_p[0], resstr, 64) < 0);
				printf("Father says son: %s\n", resstr);
			if (strcmp(resstr, str[1]) == 0)
				flag = 1;
			i = i + 1;
		}
		close(fd_c[1]);
		close(fd_p[0]);
		printf("-----------------------------------------------------------------\n");
		
	}
	
	if (pid_dan == 0)
	{
		i = 2;
		close(fd_c[1]);
		close(fd_p[0]);
		while (flag == 0)
		{
			while (size = read(fd_c[0], resstr, 64) < 0);
				printf("Son says father: %s\n", resstr);
			size = write (fd_p[1], str[i], 64);
			if (strcmp(resstr, str[3]) == 0)
				flag = 1;
			i = i + 1;
		}
		close(fd_p[1]);
		close(fd_c[0]);
		printf("------------------------------------------------------\n");
	}
	exit(0);
}