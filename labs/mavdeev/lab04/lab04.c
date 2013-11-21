#include <stdio.h>
#include <stdlib.h>

int N = 5;

int main(void) {
	
  size_t size;
  pid_t pid;
  int pipe_p[2];
  int pipe_c[2]; 	
  int flag = 0;
  char rd[64];
  char wr[64];
  int i = 0;

  if(pipe(pipe_p) < 0) {

    exit(-1); 
		
  } 
	
  if(pipe(pipe_c) < 0) {

    exit(-1); 
		
  } 
	
  pid = fork(); 

  if(pid < 0) { 
		
    exit(-1);
		
  } else if(pid > 0) {
	  
      /*inside the parent process*/
	  
      close(pipe_p[1]);  
      close(pipe_c[0]);
      	
      while(flag == 0) {
	      
        scanf("\n%[^\r\n]",wr);
        size = write(pipe_c[1], wr, 64);
        while (size = read(pipe_p[0], rd, 64) < 0);
	printf("child_say_to_parent: %s\n",rd);
	i++;
	if (i >= N)
		  
	  flag = -1;	
	  
      }
      
      close(pipe_p[0]);	
      close(pipe_c[1]);
      
      } else {
	      
	/*inside the child process*/
	      
        close(pipe_c[1]);
        close(pipe_p[0]);
		
        while(flag == 0) {
		
          while (size = read(pipe_c[0], rd, 64) < 0);
          printf("parent_say_to_child: %s\n",rd);
          scanf("\n%[^\r\n]",wr);
          size = write(pipe_p[1], wr, 64);
	  i++;
          if (i >= N)
		  
            flag = -1;	  
	  
        }
		
	close(pipe_c[0]);
	close(pipe_p[1]);		
		
      }
      
      exit(0);
      
}
