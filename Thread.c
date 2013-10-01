#include <pthread.h>
#include <stdio.h>
void *print_fnc( void *ptr );

int p = 5;

int main()
{
     pthread_t thr1, thr2;
     char *m1 = "thr1";
     char *m2 = "thr2";
     int  r1, r2;

     r1 = pthread_create( &thr1, NULL, print_fnc, (void*) m1);
     r2 = pthread_create( &thr2, NULL, print_fnc, (void*) m2);

     pthread_join( thr2, NULL);
     pthread_join( thr1, NULL);

     printf("Thread 1 devolvio: %d y el Thread 2: %d\n", r1, r2);
}


void *print_fnc( void *ptr )
{
     int i = 0;
     char *message;
     message = (char *) ptr;
     for (i; i<1000; i++) {
             p = p + 1;
             printf("%s : %d\n", (char*)message, p);
             sleep(1);
     }

}

