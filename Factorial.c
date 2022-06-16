
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

struct param_t {
    int num;
    int result;
};

int factorial(int n)
{
    if (n >= 1)
        return n * factorial(n - 1);
    else
        return 1;
}

void *thread_func(void *args)
{
    struct param_t *param = (struct param_t *)args;
    param->result = factorial(param->num);
    return (void *)NULL;
}

int main()
{
    struct param_t param;
    pthread_t thread;
    printf("Introduzca los números para encontrar su factorial: ");
    scanf("%d", &param.num);
    pthread_create(&thread, NULL, thread_func, &param);
    pthread_join(thread, NULL);
    printf("Factorial de Number: %d/n", param.result);
    return 0;
}