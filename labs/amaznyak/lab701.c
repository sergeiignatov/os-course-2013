//lab 7
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

#define FULL_PRIVEGIES 0777
#define LIST_SIZE 8192
#define MYNAME "lab701"
 
int main(){

char *array;
int md, fd, flag;
key_t key;
pid_t pid;

char pathname[] = "lab701.c";

pid = fork();
  
if (pid == -1) {
    
	printf("Error fork");
	exit(-1);
          
}

if (pid == 0) {
	if(execvp("./lab702", NULL) < 0){
			printf("%s : Error, execvp 702.\n", MYNAME);	    
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

	if((array = (char *)shmat(md, NULL, 0)) == (char *)(-1)){
		printf("%s : Error attach shared memory\n", MYNAME);
		exit(-1);
	}

	int i;
	i = 0;
	fd = open ("./lab701.c", O_RDONLY);

	while ((flag = read (fd, &array[i], 1)) > 0){
		i++;
	}

	array[i+1]=EOF;

	if (flag < 0){
		printf ("%s : Can not read file\n", MYNAME);
		exit (1);
	}

	
	i=1;
	while(i<100000000){
		i++;
	}
	printf("\nWriting of text this programm successfull\n");
	
	if(shmdt(array) < 0){
		printf("Can't detach shared memory\n");
		exit(-1);
	}
}
return 0;
} 