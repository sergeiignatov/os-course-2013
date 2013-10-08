#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[], char *envp[])
{
	int i = 0;
	int j = 0; 
	while(i != argc ){
		printf("%c" , argv[i]);
		i++;
	}
	printf("%c" , "END");
	while(envp[ j ] != 0){
		printf("%c" , envp[ j ]);
		j++;
	}

return 0;
}
