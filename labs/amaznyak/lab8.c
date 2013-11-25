//Лабараторная 8
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define N 5

static int turn;
static int interested[N];
int test_counter;
void enter_region(int thread)
{
	int other;
	other = 1 - thread;
	interested[thread] = 1;
	turn = thread;
	while (turn == thread && interested[other] == 1);
}

void leave_region(int thread)
{
	interested[thread] = 0;
}

void *mythread(void *dummy)

static void *mythread(void *dummy)

{

	pthread_t mythid; /* Для идентификатора нити исполнения */

	mythid = pthread_self();
	
	enter_region((int)mythid);
	test_counter++;
	leave_region((int)mythid);
	
	printf("Thread %d, Calculation result = %d\n", mythid, a);

	return NULL;
}

int main(void) 
{
	
	int i;
	
	for ( i = 0; i < N; i++ ) {
        pthread_create( &interested[i], (pthread_attr_t *)NULL, &mythread, (void*)i);
    }
    for ( i = 0; i < N; i++ ) {
        pthread_join(interested[i], (void **)NULL);
    }
	printf("%d\n", test_var);
	return 0;
}