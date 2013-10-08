#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[], char* env[]) {
	printf("--------------------LAB2--------------------\n");
	printf("%d\n" , argc);
	int i;
	for ( i = 0; i < argc; i++ )
		printf("%s\n" , argv[i]);
	printf("%s" , "--------------------end of argv--------------------\n");
	i = 0;
	while( env[i] != NULL ){
		printf("%s\n" , env[ i ]);
		i++;
	}
	printf("--------------------LAB2END--------------------\n");
	exit(0);
}
