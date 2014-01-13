#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>

const char* text = "Some text!";
const int text_size = 10;
const int file_size = (10 * sizeof(char));

pthread_mutex_t count_mutex     = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t  condition_var   = PTHREAD_COND_INITIALIZER;

#define FILEPATH "/tmp/mmapped.bin"
#define FILESIZE (NUMINTS * sizeof(char))


void *thread_one( void *ptr );
void *thread_two( void *ptr );

void main() {
     pthread_t thread1, thread2;

     pthread_create( &thread1, NULL, thread_one, (void*) NULL);
     pthread_create( &thread2, NULL, thread_two, (void*) NULL);

     pthread_join( thread1, NULL);
     pthread_join( thread2, NULL); 

     printf("Complete!\n");
     exit(0);
}

void *thread_one( void *ptr ) {
    printf("First thread start!\n");
    int i;
    int fd;
    int result;
    char *map;
    pthread_mutex_lock(&count_mutex);
    printf("First thread mutex lock!\n");
    fd = open(FILEPATH, O_RDWR | O_CREAT | O_TRUNC, (mode_t)0600);
    if (fd == -1) {
        perror("Error opening file for writing");
        exit(EXIT_FAILURE);
    }
    
    result = lseek(fd, file_size-1, SEEK_SET);
    if (result == -1) {
        close(fd);
        perror("Error calling lseek() to 'stretch' the file");
        exit(EXIT_FAILURE);
    }
    
    result = write(fd, "", 1);
    if (result != 1) {
        close(fd);
        perror("Error writing last byte of the file");
        exit(EXIT_FAILURE);
    }

    map = mmap(0, file_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (map == MAP_FAILED) {
        close(fd);
        perror("Error mmapping the file");
        exit(EXIT_FAILURE);
    }
    
    for (i = 1; i <=text_size; ++i) {
        map[i] = text[i-1]; 
    }

    if (munmap(map, file_size) == -1) {
        perror("Error un-mmapping the file");
    }

    close(fd);
    pthread_cond_signal( &condition_var );
    printf("First thread signal!\n");
    pthread_mutex_unlock( &count_mutex );
    printf("First thread mutex unlock!\n");
    printf("First thread end!\n");
}
void *thread_two( void *ptr ) {
    printf("Second thread start!\n");
    int i;
    int fd;
    char *map; 
    
    pthread_mutex_lock(&count_mutex);
    printf("Second thread mutex lock!\n");
    printf("Second thread cond wait!\n");
    pthread_cond_wait( &condition_var, &count_mutex );
    fd = open(FILEPATH, O_RDONLY);
    if (fd == -1) {
        perror("Error opening file for reading");
        exit(EXIT_FAILURE);
    }

    map = mmap(0, file_size, PROT_READ, MAP_SHARED, fd, 0);
    if (map == MAP_FAILED) {
        close(fd);
        perror("Error mmapping the file");
        exit(EXIT_FAILURE);
    }
    for (i = 1; i <=text_size; ++i) {
        printf("%c", map[i]);
    }
    printf("\n");

    if (munmap(map, file_size) == -1) {
        perror("Error un-mmapping the file");
    }
    close(fd);
    pthread_mutex_unlock( &count_mutex );
    printf("Second thread mutex unlock!\n");
    printf("Second thread end!\n");
}

