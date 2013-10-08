#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
	pid_t pid;
	int i;
	pid = fork();
	if (pid == 0){
		for (i = 1 ; i < 5 ; i++){
			printf("%d" , i );
		}
		return 0;
	}
	for(i = 1 ; i < 5 ; i++){
		printf("%c\n" , 'a');
	}
	
	return 0;
}
