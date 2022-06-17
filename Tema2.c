#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#define MAX 20
int array[MAX];
int key,ubi,idHilo;
int bandera = 0;                                
int current_thread = 0;
void* ThreadSearch(void* args) {               
    
    if(bandera == 1)
        pthread_exit(0);
    int num = current_thread++;
    for (int i = num * (MAX / 4); i < ((num + 1) * (MAX / 4)); i++){
        if (array[i] == key){
            bandera = 1;                        
            ubi = i;
        }
    }
}

int main(int argc, char **argv) {
    bandera = 0;
    sscanf (argv[1], "%i", &key);
    printf("Key es: %d\n",key);
    void * rest;
    int tamanho;
    sscanf (argv[2], "%i", &tamanho);
    pthread_t thread[tamanho];
    
    for(int i = 0;i < MAX;i++){
        array[i] = rand() % 10;
        printf("%d\n",array[i]);
    }
    
    for (int i = 0; i < tamanho; i++) {        
        pthread_create(&thread[i], NULL, ThreadSearch, (void*)NULL);
    }
    for (int i = 0; i < tamanho; i++) {
        pthread_join(thread[i], &rest);          
        idHilo = thread[i];
    }
    
    if (bandera == 1){
        printf("Elemento encontrado en la posicion %d y el numero de hilo es: %d \n",ubi,idHilo);
    }
    else
        printf("Elemento NO encontrado\n");
}