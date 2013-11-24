#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[], char* env[]) {

	if(execvp("./lab2", argv) < 0){
	
      printf("Ошибка, не удалось запустить 2 лабу.\n");	    
	    
    }
	exit(-1);
}
