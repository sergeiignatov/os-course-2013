#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char* argv[], char* env[]) {
	printf("\n--------------------LAB5--------------------\n");
	int fdp[2],fdc[2], p_id;
	size_t size;
	int i = 0;
	int chat = 1;
	char* msg_list[] = {"Hello!",
						"How are you?",
						"I was the first!",
						"It's so funny!",
						"Bye!"};
	char msg[16];
	
	if(pipe(fdc) < 0){
		printf("Can\'t create pipe\n");
		exit(-1); 
	} 
	if(pipe(fdp) < 0){
		printf("Can\'t create pipe\n");
		exit(-1); 
	} 
	p_id = fork(); 

	if(p_id < 0){ 
		printf("Can\'t fork child\n");
		exit(-1);
	} else if (p_id > 0) {
		/*Родитель*/
		close(fdc[0]);
		close(fdp[1]);	
		
		while (chat > 0){
			size = write(fdc[1], msg_list[i], 16);
		
			while (size = read(fdp[0], msg, 16) < 0);
			printf("FromChild: %s\n",msg);
			if (strcmp(msg, msg_list[4]) == 0)
				chat = -1;
			i++;
		}
		
		close(fdc[1]);
		close(fdp[0]);
		printf("\n--------------------LAB5PARENT_END--------------------\n");
	} else {
		/*Ребёнок*/
		close(fdc[1]);
		close(fdp[0]);
		
		while (chat > 0){
			while (size = read(fdc[0], msg, 16) < 0);
			printf("FromParent: %s\n",msg);
		
			size = write(fdp[1], msg_list[i], 16);
			if (strcmp(msg, msg_list[4]) == 0)
				chat = -1;
			i++;
		}
		
		close(fdp[1]);	
		close(fdc[0]);
		printf("\n--------------------LAB5CHILD_END--------------------\n");
	}
	exit(0);
}
