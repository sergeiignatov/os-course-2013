#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define THCOUNT 5
#define MAX_COUNTER 30

int choosing[THCOUNT]; 
int number[THCOUNT];
int counter = 0;

int my_compare_less(int a, int b, int c, int d) {
    if ( a < c )
        return 1;
    if ( a == c && b < d)
        return 1;
    return 0;
}

int max(int a[], int size) {
    int max = a[0];
    int i;
    for ( i = 0; i < size; i++ ) {
        if ( a[i] > max ) {
            max = a[i];
        }
    }
    return max;
}
void *mythread(void *dummy)
{
    int j;
    int i = (int)dummy;
    pthread_t mythid = pthread_self();
    while ( counter < MAX_COUNTER ){
        choosing[i] = 1;
        number[i] = max(number,THCOUNT)+1;
        choosing[i] = 0;
        for ( j = 0; j < THCOUNT; j++) {
            while ( choosing[j] );
            while ( number[j] != 0 && my_compare_less(number[j],j,number[i],i));
        }
        /*critical*/
        counter++;
        sleep(1);
        /*critical*/
        printf("Thread %d, Calculation result = %d\n", (int)mythid, counter);
        number[i] = 0;
    }
    printf("Thread %d finish\n",(int)mythid);
    return NULL;
}

int main()
{
    pthread_t thid[5], mythid;
    
    int i;
    for ( i = 0; i < THCOUNT; i++ ) {
        choosing[i] = 0; 
        number[i] = 0;;
    }
        
    for ( i = 0; i < THCOUNT; i++ ) {
        pthread_create( &thid[i], (pthread_attr_t *)NULL, &mythread, (void*)i);
    }
    for ( i = 0; i < THCOUNT; i++ ) {
        pthread_join(thid[i], (void **)NULL);
    }
    printf("Main finish\n");
    return 0;
}