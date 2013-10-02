#include <pthread.h>
#include <stdio.h>

void *print_fnc( void *ptr );

int main()
{
     pthread_t thr;
     char *m1 = "thr1";

     int  r1;

     r1 = pthread_create( &thr1, NULL, print_fnc, (void*) m1);

     pthread_join( thr, NULL);
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

