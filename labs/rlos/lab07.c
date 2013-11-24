#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 10
#define SYNC 3

/* Программа написана но не доделана */
int main(int argc, char* argv[], char* env[]) {

    char *array;
    int shmid;
    char pathname[] = "lab07.c"; 
    key_t key;
    if((key = ftok(pathname,0)) < 0){
        printf("Can\'t generate key\n");
        exit(-1);
    }
    int i = 1000;
    if (argc > 1) {
        /*Программа 1*/
        if((shmid = shmget(key, (SYNC+SIZE)*sizeof(char), 0666|IPC_CREAT|IPC_EXCL)) < 0){
            perror("shmget");
            exit(-1);
        }
        if((array = (char *)shmat(shmid, NULL, 0)) == (char *)(-1)){
            perror("shmat");
            exit(-1);
        }
        array[0] = 0;
        array[1] = 0;
        array[3] = 0;
        if(shmdt(array) < 0){
            perror("shmdt");
            exit(-1);
        }   
        while (i > 0){
            sleep(1);
            if((shmid = shmget(key, (SYNC+SIZE)*sizeof(char), 0)) < 0){
                perror("shmget");
                exit(-1);
            }
            if((array = (char *)shmat(shmid, NULL, 0)) == (char *)(-1)){
                perror("shmat");
                exit(-1);
            }
            array[0] = 1;
            array[2] = 1;
            while (array[1] && array[2] == 1);
            strncpy(array+SYNC*sizeof(char), argv[1],SIZE);
            array[3] = (char)(i % 255);
            printf("w:%s %d %d\n",argv[1],array[3],i);
            array[0] = 0;
            if(shmdt(array) < 0){
                perror("shmdt");
                exit(-1);
            }   
            i--;
        }        
    } else {
        /*Программа 2*/
        while (i > 0){
            sleep(1);
            if((shmid = shmget(key, (SYNC+SIZE)*sizeof(char), 0)) < 0){
                perror("shmget");
                exit(-1);
            }
            if((array = (char *)shmat(shmid, NULL, 0666|IPC_CREAT)) == (char *)(-1)){
                perror("shmat");
                exit(-1);
            }
            array[1] = 1;
            array[2] = 0;
            while (array[0] && array[2] == 0);
            char msg[SIZE];
            strncpy(msg, array+SYNC*sizeof(char), SIZE);
            printf("r:%s %d %d\n",msg,array[3],i);
            array[1] = 0;
            if(shmdt(array) < 0){
                perror("shmdt");
                exit(-1);
            }
            shmctl(shmid, IPC_RMID, NULL);
            i--;
        }
    }
    return 0;
}