#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/mman.h>
#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

#define FULL_PRIVEGIES 0777
#define SHM_SIZE 8192
#define MYNAME "lab901"
#define SEM_NAME "/mysem"

int main(){

sem_t *sema_n;
int ret,val;
char *array;
int shm_fd;
pid_t pid;

char pathname[] = "lab901.c";

if ((sema_n = sem_open(SEM_NAME, O_CREAT, 0600, 1)) ==
                                            SEM_FAILED){
    perror("sem_open");
    return -1;
}

pid = fork();
  
if (pid == -1) {
    
        printf("Error fork");
        exit(-1);
          
}

if (pid == 0) {
        if(execvp("./lab902", NULL) < 0){
                        printf("%s : Error, execvp 902.\n", MYNAME);            
                        exit(-1);
        }
}
else {  
        sem_getvalue(sema_n, &val);
        printf("semaphore value = %d\n", val);
        /* Получаем дескриптор общей памяти */
        if ((shm_fd = shm_open("my_shm", O_CREAT | O_RDWR, 0666)) ==
                                                                -1){
          perror("cannot open");
          return -1;
        }
       
        /* Устанавливаем размер общей памяти равным SHM_SIZE */
        if (ftruncate(shm_fd, SHM_SIZE*sizeof(char)) != 0){
          perror("cannot set size");
          return -1;
        }
       
        /*
         * Подключаем общую память в адресное пространство. Флаг
         * MAP_SHARED говорит, что это подключение общей памяти.
         */
        if ((array =(char *) mmap(0, SHM_SIZE, PROT_WRITE, MAP_SHARED,
                     shm_fd, 0)) == MAP_FAILED){
          perror("cannot mmap");
          return -1;
        }
       
        /* Блокируем общую память. Не забываем про этот шаг */
        if (mlock(array, SHM_SIZE) != 0){
          perror("cannot mlock");
          return -1;
        }

        int i;
        i = 0;
        fd = open ("./lab901.c", O_RDONLY);
        
        sem_wait(sema_n);
        while ((read (fd, &array[i], 1)) > 0){
                i++;
        }

        array[i+1]=EOF;
        
        if (sem_post(sema_n) != 0)
        perror("post error");
        
        munmap(array, SHM_SIZE);
        sem_close(sema_n);
        close(shm_fd);
        printf("\nWriting of text this programm successfull\n");
        
        
}
return 0;

} 
