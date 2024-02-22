#include <omp.h>
#include<stdio.h>
#define VECLEN 100

float a[VECLEN], b[VECLEN], sum;
/* Подпрограмма, в которой суммируются элементы векторов */
float dotprod()
{
    int i, rank;
    rank = omp_get_thread_num();
#pragma omp for reduction(+:sum)
    for (i = 0; i < VECLEN; i++)
    {
        sum = sum + (a[i] * b[i]);
        printf(" rank = %d i=%d\n", rank, i);
    }
    return(sum);
}

int main()
{
    int i;
    /* Инициализация элементов векторов */
    for (i = 0; i < VECLEN; i++)
        a[i] = b[i] = 1.0 * i;
    sum = 0.0;
    /* Создание множества параллельных процессов */
#pragma omp parallel
    sum = dotprod();
    printf("Sum = %f\n", sum);
}