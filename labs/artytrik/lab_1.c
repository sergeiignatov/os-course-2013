#include  <stdio.h>
#include  <sys/types.h>
#include <stdlib.h>
#include <unistd.h>

#define   MAX_COUNT  20

void  ChildProcess(void); //дочерний процесс               
void  ParentProcess(void); //процесс родителя

void  main(void)
{
     pid_t  pid;

     pid = fork();
	 if (pid == -1)
        {
            printf ("Can't fork!!\n"); //обработчик ошибок при вызове fork
            exit (-1);
        }
     else if (pid == 0) 
          ChildProcess();
     else 
          ParentProcess();
}

void  ChildProcess(void)
{
     int   i;

     for (i = 1; i <= MAX_COUNT; i++)
          printf("   This line is from child, value = %d\n", i);
     printf("   *** Child process is done ***\n");
}

void  ParentProcess(void)
{
     int   i;

     for (i = 1; i <= MAX_COUNT; i++)
          printf("This line is from parent, value = %d\n", i);
     printf("*** Parent is done ***\n");
}