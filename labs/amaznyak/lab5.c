/*Программа, организующая чат между двумя запущенными копиями программы с помощью FIFO*/
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <semaphore.h>
#include <string.h>

#define NAME_LENGTH 16
#define MESSAGE_LENGTH 64


char* getBotAnswer(char* msg) {
    // подразумемвается что капсом никто не пользуется.
    if ( strcmp(msg, "привет") == 0 ||
        strcmp(msg, "хай") == 0 || 
        strcmp(msg, "ку") == 0 || 
        strcmp(msg, "ку-ку") == 0 || 
        strcmp(msg, "прив") == 0 ) {
        if (rand() % 10 > 5)
            return "и тебе привет";
        else return "прив";
    } 
    if ( strcmp(msg, "как оно?") == 0 ||
        strcmp(msg, "как дела?") == 0 || 
        strcmp(msg, "как ты?") == 0 || 
        strcmp(msg, "как сам?") == 0 ) {
        if (rand() % 10 > 5) {
            return "все отлично. а ты как?";
        } else {
            return "спасибо, хорошо. а ты как?";
        }
    }
    if ( strcmp(msg, "чем занят?") == 0 ||
        strcmp(msg, "что делаешь?") == 0 ) {
        if (rand() % 10 > 5) {
            return "с тобой болтаю. а ты?";
        } else {
            return "музыку слушаю. а ты?";
        }
    }
    if ( strcmp(msg, "bye") == 0 ) {
        return "bye";
    }
    
    return "Я не понимаю";
}

int main(int argc, char* argv[], char* env[]) {
    
    int p_id;
    
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
    
    if (argc > 1) {
        /*BOT LOGIC*/
        int fd_friend, fd_bot;
        char answer[MESSAGE_LENGTH];
        if((fd_friend = open(friend_name, O_WRONLY)) < 0){
            printf("Can\'t open FIFO for writting\n");
            return -1; 
        }   
        if( (fd_bot = open(my_name, O_RDONLY)) < 0 ){
            printf("Can\'t open FIFO for reading\n");
            return -1; 
        } 
        strcpy(msg, "Hello, ");
        strncat(msg, friend_name, MESSAGE_LENGTH);
        size_t size = write(fd_friend, msg, MESSAGE_LENGTH);            
                
        if(size != MESSAGE_LENGTH)
            return -1;
        do {
            memset(msg, '\0', MESSAGE_LENGTH);
            memset(answer, '\0', MESSAGE_LENGTH);
            size = read(fd_bot, msg, MESSAGE_LENGTH);
            
            strcpy(answer,getBotAnswer(msg));
            size = write(fd_friend, answer, MESSAGE_LENGTH);            
                
            if(size != MESSAGE_LENGTH)
                return -1;
        } while (strcmp(msg, "bye") != 0 && strcmp(answer, "bye") != 0 );
        close(fd_friend);
        close(fd_bot);
    } else {
        int fd;
        p_id = fork();
             
        if( p_id < 0 ){ 
            printf("Can\'t fork child\n");
            exit(-1);
        } else if ( p_id > 0 ) {
            if((fd = open(friend_name, O_WRONLY)) < 0){
                printf("Can\'t open FIFO for writting\n");
                return -1; 
            }
            /*WRITING*/
            do {
                memset(msg, '\0', MESSAGE_LENGTH);
                scanf("\n%[^\r\n]",msg);
                printf("%s: %s\n",my_name,msg);

                size_t size = write(fd, msg, MESSAGE_LENGTH);            
                
                if(size != MESSAGE_LENGTH)
                    return -1; 
            } while (strcmp(msg, "bye") != 0);
            close(fd);
        } else {
            if( (fd = open(my_name, O_RDONLY)) < 0 ){
                return -1; 
            } 
            /*READING*/
            do {
                memset(msg, '\0', MESSAGE_LENGTH);

                size_t size = read(fd, msg, MESSAGE_LENGTH);

                if( size <= 0 )
                    return -1;
                printf("%s: %s\n",friend_name,msg);
            } while (strcmp(msg, "bye") != 0);
            close(fd);
        }
    }
    remove(my_name);
        return 0;
}
