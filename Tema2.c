#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

#define MAX 20
int varGlob = 0;

struct estructura{
    int vec[MAX];
    int value;
    int hilo;
    int flag;
    int n;
};

void *thread_secuencial(void *arg){
    struct estructura *vector = (struct estructura *)arg;

    if(varGlob==0){
        for(int r=0; r<vector->n; r++){
            if(vector->value == vector->vec[r]){
                int hilo = vector->hilo-1;
                printf("Se encontro el valor %d en el hilo # %d en la posicion %d", vector->value, vector->hilo, (vector->n*hilo)+r);
                varGlob = 1;
                break;
            }
        }
    }
}


int main(int argc, char *argv[]){ 
    time_t t;
    int i, v[MAX],value=0,cantidades=0, j=0, hilos=0, n=0,m=0, k=0, numero, flag=0;
    srandom(time(&t)); 
    for (i=0;i<MAX;i++){
        numero=random()%10;
        v[i]=numero;

    }
    for(i=0; i<MAX; i++){
        printf("%d ",v[i]);
    }
    printf("\n");



    if (argv[0])value=atoi(argv[1]);
    if (argv[1])cantidades=atoi(argv[2]);
    n=MAX/cantidades;
    m=n;
    int vector[n];
    for(int r=0;r<n;r++)vector[r]=0;
    struct estructura vec_struct[cantidades];
    

    
    pthread_t thread[cantidades];      
    for (int i=0; i<cantidades; i++){
        for (int r=j; r<m; r++){
            vector[k] = v[r];
            vec_struct[i].vec[k] = v[r];
            vec_struct[i].hilo = i+1;
            vec_struct[i].value = value;
            vec_struct[i].flag = 0;
            vec_struct[i].n = n;
            k++;
        }

        k=0;
        j=m;
        m=m+n;

    }
    for (int i=0; i<cantidades; i++){
        if(varGlob==0)pthread_create(&thread[i],NULL,&thread_secuencial,&vec_struct[i]);
        else break;
    }

    for (int i=0; i<cantidades; i++)pthread_join(thread[i],NULL);




    printf("\n");
    return 0;
}