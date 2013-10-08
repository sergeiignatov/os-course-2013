
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[], char* env[]) {
	printf("--------------------LAB3--------------------\n");
	printf("%d\n",argc);
	execl(argv[1], argv[1], argv[0]); 
	printf("Ошибка передачи управления\n");
	printf("--------------------LAB3END--------------------\n");
	exit(0);
}

