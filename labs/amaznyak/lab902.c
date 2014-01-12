#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/mman.h>
#include <semaphore.h>
#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

#define LIST_SIZE 8192
#define MYNAME "lab902" 
int main(){

char *array;
int fd;
sem_t *sema_n;
 int ret,val;
 
printf("%s : Im start \n", MYNAME);

char pathname[] = "lab901.c";

/* Получаем дескриптор общей памяти */
  if ((shm_fd = shm_open("my_shm", O_CREAT | O_RDWR, 0666)) ==
                                                          -1){
    perror("cannot open");
    return -1;
  }
 
  /* Устанавливаем размер общей памяти равным SHM_SIZE */
  if (ftruncate(shm_fd, SHM_SIZE) != 0){
    perror("cannot set size");
    return -1;
  }
 
  /*
   * Подключаем общую память в адресное пространство. Флаг
   * MAP_SHARED говорит, что это подключение общей памяти.
   */
  if ((array = (char *) mmap(0, SHM_SIZE, PROT_WRITE, MAP_SHARED,
               shm_fd, 0)) == MAP_FAILED){
    perror("cannot mmap");
    return -1;
  }
 
  /* Блокируем общую память. Не забываем про этот шаг */
  if (mlock(vaddr, SHM_SIZE) != 0){
    perror("cannot mlock");
    return -1;
  }

int i;
i = 0;
printf("%s : code in lab901.c:\n", MYNAME);
printf("-----------------------------------------------------------\n\n");

while (array[i] != EOF ){
        
        putchar(array[i]);
        ++i;
}
printf("%s \n", array);

munmap(vaddr, SHM_SIZE);
close(shm_fd);
/* Удаляем сегмент общей памяти */
shm_unlink("my_shm");

printf("%s : \nAll shared mamory released\n\n", MYNAME);

return 0;

} 

