#include <stdio.h>
#include <stdlib.h>

int main(void) {
	
  pid_t pid;
  pid = fork();
  if (pid == -1) {
	  
    exit(-1);
	  
  } 
  else if (pid == 0) {
	  
    /*inside the child process
     *let's try to run the program "hello"*/
	  
    if(execvp("./hello", NULL) < 0){
	
      printf("fail :(\n");	    
      exit(-1);
	    
    }

    /*so works shell's "invitation" - $*/ 
    
  } else {
	  
    /*inside the parent process
     *let's print the child pid*/
	  
    printf("child pid = %d\n", pid);
	  
  }
  
  return 0;
	
}