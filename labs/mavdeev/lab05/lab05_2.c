#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(voud) {

  int fd;
  int pid;     
  char to_me[] = "lab052";
  char to_companion[] = "lab051";    
  char wr[64];
  char rd[64];
  
  (void)umask(0); 

  printf("Waiting for connection...\n");	
	
  if(mknod(to_me, S_IFIFO | 0666, 0) < 0) {
    printf("Can\'t create FIFO\n");
    exit(-1); 
  }
  
  while (access(to_companion, 0) == -1);
  printf("completed!\n");
  
  pid = fork();
         
  if( pid < 0 ) { 
    printf("Can\'t fork child\n");
    exit(-1);
  } else if ( pid > 0 ) {

    /*inside the parent process
     *let's try to write into FIFO*/
	  
    if((fd = open(to_companion, O_WRONLY)) < 0) {
      printf("Can\'t open FIFO for writting\n");
      exit(-1); 
    }	  
    do {
	    
      scanf("\n%[^\r\n]",wr);
      printf("me: %s\n",wr);
      write(fd, wr, 64);            
            
    } while (strcmp(wr, "exit") != 0);
    
    close(fd);
  } else {
	  
    /*inside the child process
     *let's try to read from FIFO*/	  
	  
    if( (fd = open(to_me, O_RDONLY)) < 0 ){
      printf("Can\'t open FIFO for reading\n");
      exit(-1); 
    }   
    do {
	    
      read(fd, rd, 64);
      printf("companion: %s\n",rd);
	    
    } while (strcmp(rd, "exit") != 0);
    
    close(fd);
  }
  
  remove(to_me);
  
  return 0;
  
}