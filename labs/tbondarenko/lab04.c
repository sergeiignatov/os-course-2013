#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

int main(){
	int fd;
	(void)umask(0);
	if((fd = open("myfile", O_RDONLY)) < 0){
		printf("Can\'t open file\n");	
		exit(-1);
	}
	if(close(fd) < 0){
	printf("Can\'t close file\n");
	}
	return 0;
}