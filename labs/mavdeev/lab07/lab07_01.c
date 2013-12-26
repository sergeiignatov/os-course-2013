#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {

  int fd;
  char to_companion[] = "lab072";    
  char wr[64];
  
  (void)umask(0); 

  printf("Waiting for connection...\n");	
	 
  while (access(to_companion, 0) == -1);
  
  printf("completed!\n");
  
  if((fd = open(to_companion, O_WRONLY)) < 0) {
  
    printf("Can\'t open FIFO for writting\n");
    exit(-1);
	
  } 
  
  FILE *file; 
  char *fname = "lab07_01.c";
  file = fopen (fname,"r");
  
  while(fgets(wr,sizeof(wr),file)){
  
    write(fd,wr,sizeof(wr));
  
  }
 
  fclose(file);
  close(fd);

  return 0;
  
}
