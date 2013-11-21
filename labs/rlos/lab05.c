/*Программа, организующая чат между двумя запущенными копиями программы с помощью FIFO*/
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <string.h>

#define NAME_LENGTH 32
#define MESSAGE_LENGTH 16
/* Возникает просто миллион вопросов, 
хотя конечно по факту запуск этой программы в двух экземплярах, соответствует требованию лабораторки, все же.
1. Зачем создавать два разных процесса для чтения и записи? Все так же это можно было делать и в одном процессе
2. Зачем тратить ресурсы для того чтобы перед каждой записью/чтением инициализировать канал связи?
3. И конечно жаль что вы не захотели делать чат с ботами. 
Но этого конечно вполне достаточно чтобы сдать лабораторку, если вы ответите на поставленные вопросы
(желательно чтобы ответ был связным, логичным и хоть что то объяснял)*/ 

int main(int argc, char* argv[], char* env[]) {

	int fd, p_id;
     
    char my_name[NAME_LENGTH];
    char friend_name[NAME_LENGTH];
    
    char msg[MESSAGE_LENGTH];
    
    memset(my_name, '\0', NAME_LENGTH);
    memset(friend_name, '\0', NAME_LENGTH);
    
    printf("Введите ваш ник: ");
    scanf("%s",my_name);
    if (access(my_name, 0) != -1){
        printf("Ник занят!\n");
        return -1;
    }
	(void)umask(0); 

    if(mknod(my_name, S_IFIFO | 0666, 0) < 0){
		perror("mknod");
		return -1; 
	}    
    
    printf("Введите ник собеседника: ");
    scanf("%s",friend_name);
    
    if (access(friend_name, 0) == -1){
        printf("Собеседник не найден!\n");
        remove(my_name);
        return -1;
    }
        
    printf("Соединение установлено!\n");
    
    p_id = fork();
         
	if( p_id < 0 ){ 
		printf("Can\'t fork child\n");
		exit(-1);
	} else if ( p_id > 0 ) {
        /*WRITING*/
        do {
            memset(msg, '\0', MESSAGE_LENGTH);
            gets(msg);
            printf("%s: %s\n",my_name,msg);
            if((fd = open(friend_name, O_WRONLY)) < 0){
                printf("Can\'t open FIFO for writting\n");
                return -1; 
            }
            size_t size = write(fd, msg, MESSAGE_LENGTH);            
            
            if(size != MESSAGE_LENGTH){
                printf("Can\'t write all string to FIFO\n"); 
                return -1; 
            }
        } while (strcmp(msg, "bye") != 0);
        close(fd);
	} else {
        /*READING*/
        do {
            memset(msg, '\0', MESSAGE_LENGTH);
            if( (fd = open(my_name, O_RDONLY)) < 0 ){
                printf("Can\'t open FIFO for reading\n");
                return -1; 
			} 
            size_t size = read(fd, msg, MESSAGE_LENGTH);

			if(size < 0){
                printf("Can\'t read string\n"); 
                return -1; 
            }
            printf("%s: %s\n",friend_name,msg);
        } while (strcmp(msg, "bye") != 0);
        close(fd);
	}
    remove(my_name);
	return 0;
}
