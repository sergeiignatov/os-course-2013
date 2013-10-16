#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

int main(){
	int fd;
	(void)umask(0); // это строка не обязательна так как вы 
			//ничего не создаете, а значит вам не надо беспокоиться о неверно выставленных правах на файл
	if((fd = open("myfile", O_RDONLY)) < 0){
		printf("Can\'t open file\n");	
		exit(-1);
	}
	// ну раз уж вы открыли файл на чтение можно и прочитать с него хоть что-то, а не закрывать сразу
	if(close(fd) < 0){
	printf("Can\'t close file\n");
	}
	return 0;
}
