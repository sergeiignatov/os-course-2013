//laboratory 5 with five extra threads

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define thcount 5

int choose[thcount]; 
int number[thcount];

int a = 0;


int compare(int a, int b, int c, int d) {

  int result = 0;
	
  if (a < c) {
	  
    result = 1;
	  
  } else if (a == c && b < d) {
	  
    result = 1;
	  
  }
  
  return result;
    
}

int max() {
	
  int result = number[0];
	
  int i;
	
  for (i = 1; i < thcount; i++) {
	    
    if (number[i] > result) {
		
      result = number[i];
		
    }
	
  }
    
  return result;
    
}

static void *mythread(void *dummy) {

  pthread_t mythid;
  mythid = pthread_self();
	
  int j;
  int i = *(int*)dummy;

  //bakery algorithm
	
  choose[i] = 1;
  number[i] = max() + 1;
  choose[i] = 0;
	
  for (j = 0; j < thcount; j++) {
	  
    while(choose[i]);
    while(number[j] != 0 && compare(number[j],i,number[i],j));
	    
  }

  //critical section
  
  a = a + 1;

  printf("Thread %d, Calculation result = %d\n", mythid, a);
  
  number[i] = 0;
  
  //end critical section

  return NULL;
	
}

int main() {
	
  pthread_t thid[thcount], mythid;
	
  int result;
	
  int i;
	
  for ( i = 0; i < thcount; i++ ) {
	  
    choose[i] = 0; 
    number[i] = 0;
	  
  }   
  
  for ( i = 0; i < thcount; i++ ) {
	  
    result = pthread_create( &thid[i], (pthread_attr_t *)NULL, &mythread, (void*)&i);
	  
    if(result != 0) {
	    
      printf ("Error on thread create, return value = %d\n", result);
      exit(-1);
	    
    }
    
    printf("Thread created, thid = %d\n", thid[i]);
    
  }
  
  mythid = pthread_self();

  a = a + 1;

  printf("Thread %d, Calculation result = %d\n", mythid, a);
  
  for ( i = 0; i < thcount; i++ ) {
	  
    pthread_join(thid[i], (void **)NULL);
	  
  }
  
  return 0;
  
}