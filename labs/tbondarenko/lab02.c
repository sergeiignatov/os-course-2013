#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[], char *envp[])
{
	int i = 0;
	int j = 0; 
	while(i != argc ){
		printf("%s\n" , argv[i]);
		i++;
	}
	// "END это тоже строка)))"
	printf("%c" , "END");
	while(envp[ j ] != NULL){
		printf("%s\n" , envp[ j ]);
		j++;
	}

	return 0;
}
