#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

#define number_of_records 5
#define name_length 64
#define email_length 64
#define record_length (name_length + email_length + 2)

int main(int argc, char* argv[], char* env[]) {
	
  if (argc != 2 || (strcmp(argv[1], "set") != 0 && strcmp(argv[1], "find") != 0)) {
	  
    printf("Function must be called with the argument 'set' or 'find'\n");
    exit(-1);
	  
  }

  char *data_base; /* A pointer to the shared memory */

  int shmid; /* IPC descriptor for the shared memory */

  char pathname[] = "lab06.c"; /* Name of the file used to generate the key */

  key_t key; /* IPC key */ 


  /* Generate IPC key */

  if((key = ftok(pathname,0)) < 0) {
    printf("Can\'t generate key\n");
    exit(-1);
  }
  
  /* Trying to create a shared memory exclusively for the generated key
   */

  if((shmid = shmget(key, number_of_records*record_length*sizeof(char), 0666|IPC_CREAT|IPC_EXCL)) < 0) {

    if(errno != EEXIST) {

      printf("Can\'t create shared memory\n");
      exit(-1);
			
    } else {

      if((shmid = shmget(key, number_of_records*record_length*sizeof(char), 0)) < 0) {
	      
        printf("Can\'t find shared memory\n");
        exit(-1);
	      
      }
      
    }
    
  }
 

  /* Trying to display the shared memory into the address space of the current process
   */ 

    if((data_base = (char*)shmat(shmid, NULL, 0)) == (char*)(-1)) {
	    
      printf("Can't attach shared memory\n");
      exit(-1);
	    
    }

  if(strcmp(argv[1], "set") == 0) {
	  
    char name[name_length];
    char email[email_length];
    int i;
    for(i = 0; i < number_of_records; i++){

      memset(name, '\0', name_length);
      memset(email, '\0', email_length);	    
      printf("Enter the record number %d\nEnter name: ", i);
      scanf("\n%[^\r\n]",name);
      printf("Enter email: ");
      scanf("\n%[^\r\n]",email);
	    
      strncpy(data_base+(i*record_length)*sizeof(char), name, name_length);
      strncpy(data_base+(i*record_length+name_length)*sizeof(char), "\0", name_length);
      strncpy(data_base+(i*record_length+name_length+1)*sizeof(char), email, email_length);
      strncpy(data_base+((i+1)*record_length-1)*sizeof(char), "\0", email_length);
    
    }    
	  
  } else {
	  
    char name[name_length];
    memset(name, '\0', name_length);
	  
    printf("Enter name: ");
    scanf("\n%[^\r\n]",name);
	  
    int i;
    int result = 0;
    for(i = 0; i < number_of_records; i++) {
	    
      char tempname[name_length];	    
      memset(tempname, '\0', name_length);
      strncpy(tempname, data_base+(i*record_length)*sizeof(char), name_length);
      if (strcmp(tempname, name) == 0) {
	      
        result = 1;
	char tempemail[email_length];
	memset(tempemail, '\0', email_length);
	strncpy(tempemail, data_base+(i*record_length+name_length+1)*sizeof(char), email_length+1);
	      
	printf("%s %s\n",tempname,tempemail);
	      
      }
      
    }	
    
  }


  /* Remove the shared memory address space of the current process
   */ 

  if(shmdt(data_base) < 0) {
		
    printf("Can't detach shared memory\n");
    exit(-1);
		
  }
	
  return 0;
  
}
