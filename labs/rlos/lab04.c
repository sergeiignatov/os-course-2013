/* Программа выводящая первые 13 байт файла myfile*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <fcntl.h>

int main(int argc, char* argv[], char* env[]) {
	printf("--------------------LAB4--------------------\n");
	int fd;
	size_t size = 13;
	char* string = (char*)malloc(size*sizeof(char));
	(void)umask(0); 
	
	if((fd = open("myfile", O_RDONLY)) < 0){
		printf("Can\'t open file\n");
		exit(-1); 
	}
	
	if(size != read(fd, string, size)){
		printf("Can\'t read first %d bytes\n", size); 
		exit(-1); 
	} 
	
	printf("%s\n",string);

	if(close(fd) < 0){ 
		printf("Can\'t close file\n");
	}
	printf("--------------------LAB4END--------------------\n");
	exit(0);
}
