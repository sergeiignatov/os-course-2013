#include <stdio.h>

int main(int argc, char *argv[]) {

  if(argv[1] == NULL) {
	 
    argv[1] = "World";
	  
  } 
  printf("Hello %s!",argv[1]);
	  
  return 0;
  
}