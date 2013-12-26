#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {

  int fd;    
  char to_me[] = "lab072";
  char rd[64];
  
  (void)umask(0); 
	
  if(mknod(to_me, S_IFIFO | 0666, 0) < 0) {
    printf("Can\'t create FIFO\n");
    exit(-1); 
  }
         
  if( (fd = open(to_me, O_RDONLY)) < 0 ){
  
    printf("Can\'t open FIFO for reading\n");
    exit(-1);
	
  }   

	    
      while(read(fd, rd, 64) != 0){
      printf("%s",rd);
	  }
	    
    
  close(fd);
  remove(to_me);
  
  return 0;
  
}