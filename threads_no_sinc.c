#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/syscall.h>



int contador = 0; // Nuestra variable global de prueba


#define ITERACIONES 10000 // Cantidad de incrementos que realizara cada hilo


/*
	Funcion local para obtener el thread id
*/
int get_thread_id(void); 

/*
	Funcion local que sera ejecutada por cada hilo
*/
void * incrementar(void* parametro_sin_usar);


int main(){

	pthread_t hilo1;
	pthread_t hilo2;

	// Creamos los hilos. Los mismos empiezan a ejecutar "inmediatamente"
	pthread_create(&hilo1, NULL, incrementar, NULL);	
	pthread_create(&hilo2, NULL, incrementar, NULL);	


	// Esta funcion bloquea al hilo actual (el del main) hasta que el hilox finaliza su ejecucion
	pthread_join(hilo1, NULL);
	pthread_join(hilo2, NULL);

	// El valor esperado es ITERACIONES x 2 porque tenemos dos hilos
	printf("Valor esperado/obtenido: %d/%d\n", ITERACIONES * 2, contador);

	return 0;
}



void* incrementar(void* parametro_sin_usar){

	int i;

	for (i = 0; i < ITERACIONES; i++){
		contador++;
		//printf("H[%d]: Valor actual: %d\n", get_thread_id(), contador);
	}
	
	return;

}

int get_thread_id(void){
	// Syscall wrapper casero, porque no esta implementado en la standard library (tipear "man gettid")
	return (int) syscall(SYS_gettid);
}

