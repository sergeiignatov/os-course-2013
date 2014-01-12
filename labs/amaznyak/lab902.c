#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

#define LIST_SIZE 8192
#define MYNAME "lab902" 
int main(){

char *array;
int md, flag;
key_t key;
int fd;
printf("%s : Im start \n", MYNAME);

char pathname[] = "lab701.c";

if((key = ftok(pathname, 0)) < 0){
printf("%s : Can\'t generate key\n", MYNAME);
}

if((md = shmget(key, LIST_SIZE*sizeof(char), 0)) < 0){
printf("%s : Can\'t find shared memory\n", MYNAME);
//exit(-1);
}

if((array = (char *)shmat(md, NULL, 0)) == (char *)(-1)){
printf("%s : Can't attach shared memory\n", MYNAME);
}

int i;
i = 0;
printf("%s : code in lab701.c:\n", MYNAME);
printf("-----------------------------------------------------------\n\n");

while (array[i] != EOF ){
        
        putchar(array[i]);
        ++i;
}
printf("%s \n", array);
if(shmctl(md, IPC_RMID, NULL) < 0){
printf("%s : Can't free shared memory\n", MYNAME);

}

printf("%s : \nAll shared mamory released\n\n", MYNAME);

return 0;
<<<<<<< HEAD
} 
=======
} 
