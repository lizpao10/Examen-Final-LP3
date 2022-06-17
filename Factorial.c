
#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
unsigned long long *factorial(unsigned long long n)
{
    unsigned long long *r= (unsigned long long*)malloc(1*sizeof(unsigned long long));
    unsigned long long i= 1,f= 1;
    while (i<= n)
    {
        f= f*i;
        i= i +1;
    }
    r[0]=f;
    printf("Factorial de %lld: %lld\n", n, f);
    return r;
}

void *factorial_(void *args)
{
    unsigned long long n= *((unsigned long long*)args);
    return (void*)factorial(n);
}

int main(int argc , char **argv){
    int conta=0;
    char lectura[10000];
    printf("Ingresar valores para calcular factorial: ");
	scanf("%[^\n]%*c",lectura);
	char *p;
	p =lectura;
	while (*p != '\0') {
		if( *p == ' ') conta++;
		p++;
	}
    unsigned long long valores[conta+1];
    int j=0;
    char *a;
    a =lectura;
    while (*a != '\0') {
		if( !(*a == ' '))
        {
            valores[j]= (unsigned long long) strtol(a, NULL, 10);
            if(valores[j]>9)a++;
            j++;
        } 
		a++;
	}
    pthread_t thread[conta+1];
    unsigned long long auxi;
    for (int i = 0; i < conta+1; i++)
    {
        auxi= valores[i];
        pthread_create(&thread[i], NULL, factorial_,&auxi);
        pthread_join(thread[i],NULL);
    } 
}