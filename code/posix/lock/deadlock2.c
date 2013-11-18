pthread_mutex_lock(&mutex_1);
while ( pthread_mutex_trylock(&mutex_2) )  /* Test if already locked   */
{
   pthread_mutex_unlock(&mutex_1);  /* Free resource to avoid deadlock */
   ...
   /* stall here   */
   ...
   pthread_mutex_lock(&mutex_1);
}
count++;
pthread_mutex_unlock(&mutex_1);
pthread_mutex_unlock(&mutex_2);


