//lab 6
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

int main(){

char *array;
int md, fd, flag;
key_t key;
pid_t pid;

char pathname[] = "lab601.c";

pid = fork();
  
if (pid == -1) {
    
	printf("Error fork");
	exit(-1);
          
}

if (pid == 0) {
	if(execvp("./lab602", NULL) < 0){
			printf("%s : Error, execvp 602\n", MYNAME);	    
			exit(-1);
	}
}
else {
	if((key = ftok(pathname, 0)) < 0){
		printf("%s : Error of generate key\n", MYNAME);
		exit(-1);
	}
	
	if((md = shmget(key, LIST_SIZE*sizeof(char), FULL_PRIVEGIES|IPC_CREAT|IPC_EXCL)) < 0){
		if(errno != EEXIST){
			printf("%s : Error of create shared memory\n", MYNAME);
			exit(-1);
		}
		else {
			if((md = shmget(key, LIST_SIZE*sizeof(char), 0)) < 0){
				printf("%s : Error of find shared memory\n", MYNAME);
				exit(-1);
			}
		}
	}
	
}
    return 0;
}
