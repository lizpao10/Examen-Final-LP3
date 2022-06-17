#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

#define MAX 20

typedef struct s_indices
{
	int ini;
	int fin;
}indices;

void put_numbers();
int rand_limit(int lim);
void buscar(void *arg);

int num_objetivo = -1;
int terminacion = 0;
int *array;

int main(int argc, char **argv)
{
	int i, cant_hilos = atoi(argv[2]);
	num_objetivo = atoi(argv[1]);
	printf("CREANDO ARRAY");
	array = malloc(MAX*sizeof(int));
	printf("ARRAY CREADO EXITOSAMENTE");
	
	srandom(time(0));
	printf("CREADO EXITOSAMENTE");
	put_numbers(array);
	
	if(cant_hilos > MAX)
		cant_hilos = MAX;
	pthread_t hilo[cant_hilos];
	
	int tam2 = MAX/cant_hilos;
   	
   	indices index[cant_hilos];
   	for(i = 0; i < cant_hilos; i++)
   	{
   		index[i].ini = i*tam2;
   		if(i == cant_hilos-1)
   			index[i].fin = MAX;
   		else
   			index[i].fin = i*tam2 + tam2;
   		pthread_create(&hilo[i], NULL, (void*)&buscar, (void*)&index[i]);
   	}
   	
   	void *flag;
   	int aux;
   	indices result;
   	result.ini = -1; result.fin = -1;
   	for(i = 0; i < cant_hilos; i++)
   	{
   		pthread_join(hilo[i], &flag);
   		aux = (int)flag;
   		if(aux >= 0)
   		{
   			//printf("Flag: %d\n", aux);
   			result.ini = aux;
   			result.fin = i;
   		}
   	}
   	
   	printf("Array:\n");
   	for(i = 0; i < MAX; i++)
   		printf("%d ", array[i]);
   	printf("\n\n"); 
   	
   	if(result.ini >= 0) 
   		printf("El numero %d fue encontrado en el indice %d por el proceso %d.\n", num_objetivo, result.ini, result.fin);
   	else
   		printf("El numero %d no fue encontrado.\n", num_objetivo);
	
	return 0;
}

void buscar(void *arg)
{
	indices index =  *((indices*)arg);
	int i;
	for(i = index.ini; i < index.fin && terminacion == 0; i++)
	{
		if(array[i] == num_objetivo)
		{
			terminacion = 1;
			//printf("Se encontro\n");
			int aux1 = (int) i; //Ver el comentario de abajo
			return (void*) i;
		}
	}
	//printf("No se encontro\n");
	int menos_uno = -1;
	int aux2 = (int) menos_uno; //No se porque, pero esta linea "innecesaria" hace que retorne corretamente el numero
	return (void*) menos_uno;
}

int rand_limit(int lim)
{
	int divisor = RAND_MAX/lim;
	int valor;
	
	do{
	valor = random()/divisor;
	}while(valor > lim);
	
	return valor;
}

void put_numbers()
{
	int i;
	for(i = 0; i < MAX; i++)
	{
		array[i] = rand_limit(10);
	}
}
