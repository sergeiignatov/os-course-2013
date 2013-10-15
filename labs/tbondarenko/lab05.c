#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
	int fd1[2], fd2[2], pid;
	int i = 0;
	size_t size;
	char resstring[21];
	char* speaking1[] = {"Hello!", "How are you?", "Do you like coffee?", "Have you got a pet?", "Good bye=*"};
	char* speaking2[] = {"Hello!", "All right=)", "No", "Yes", "BB"};
	
	if(pipe(fd1) < 0){

		printf("Can\'t create pipe1\n");
		exit(-1); 
	} 
	
	if(pipe(fd2) < 0){

		printf("Can\'t create pipe2\n");
		exit(-1); 
	} 
	
	pid = fork();
	
	if(pid <0){ 

		printf("Can\'t fork child\n");
		exit(-1);

	} else if (pid > 0) {
		close (fd1[1]);
		close (fd2[0]);
		
		for (i = 0; i < 5; i++)
		{
			size = write(fd2[1], speaking1[i], 21);
			
			if(size != 21){
			printf("Can\'t write all string 1\n"); 
			exit(-1);			
			}
			
			size = read(fd1[0], resstring, 21);
		 
			if(size < 0){

			printf("Can\'t read string\n"); 
			exit(-1); 
			} 
			printf("%s\n",resstring);
		}
		
		
		close (fd1[0]);
		close (fd2[1]);
		
		}
			else{
				close (fd1[0]);
				close (fd2[1]);
		
				for (i = 0; i < 5; i++)
				{
					size = write(fd1[1], speaking2[i], 21);
			
					if(size != 21){
					printf("Can\'t write all string 2\n"); 
					exit(-1);			
					}
			
					size = read(fd2[0], resstring, 21);
				
					if(size < 0){

					printf("Can\'t read string\n"); 
					exit(-1); 
					} 
					printf("%s\n",resstring);
				}
				
		
				close (fd1[1]);
				close (fd2[0]);
		
				}
	return 0;
}