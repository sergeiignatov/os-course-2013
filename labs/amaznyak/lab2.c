#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void main(int argc, char* argv[], char* env[]) {
	
	//argc это количество элементов в массиве argv
	printf("ВЫВОДИМ аргументы переданые в main \n В массиве argv %d элементов:\n" , argc);
	int i = 0;
	while(i < argc){
		printf("%d. %s \n " , i, argv[i]);
		i++;
	}
	
	//т.к. мы не знаем кол-во элементов в env идем по массиву пока указатель не будет равен 0.
	printf("Массив env: \n");
	int j = 0;
	while( env[j] != NULL ){
		printf("%d. %s\n" ,j ,env[j]);
		j++;
	}

	exit(0);
}
