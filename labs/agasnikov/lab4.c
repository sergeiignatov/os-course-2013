#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[], char* env[]) 
  {
    int filedes_p[2];
    int filedes_c[2];
    int p_id;
    size_t size;
    int i = 0;
    int point = 0;
    int ex_cond = 3;
    char* message_list1[] = {"What is your name!?","How old are you!?","Goodbye!!!"};
    char* message_list2[] = {"My name is Sandron","I'm 21","Bye!!!"};
    char message[32];

    if(pipe(filedes_p) < 0) 
      {
        printf("Errrrrror");
        exit(-1); 
      }

    if(pipe(filedes_c) < 0) 
      {
        printf("Errrrrror");
        exit(-1); 
      } 
    
    p_id = fork ();

    if(p_id < 0) 
      { 
        printf("Errrrrror");
        exit(-1);
      } else 
        if(p_id > 0) 
          {
            close(filedes_p[1]);  
            close(filedes_c[0]);
            while(point == 0) 
              {
                size = write(filedes_c[1], message_list1[i], 32);
                while (size = read(filedes_p[0], message, 32) < 0);
                  printf("I tyt maloy otvetil: %s\n",message);
                i++;
                if(i >= ex_cond)
                  point = -254;
              }
            close(filedes_p[0]);	
            close(filedes_c[1]);
          } else 
            {
              close(filedes_p[0]);	
              close(filedes_c[1]);
              while(point == 0) 
                {
                  while (size = read(filedes_c[0], message, 32) < 0);
                    printf("I tyt batya skazal: %s\n",message);
                  size = write(filedes_p[1], message_list2[i], 32);
                  i++;
                  if(i >= ex_cond)
                    point = -254;
                }
              close(filedes_p[1]);  
              close(filedes_c[0]);
            }
    exit(0);   
  }
