#include <omp.h>
#include <stdio.h>
int main()
{
    int i, n;
    float a[100], b[100], sum;

    n = 100;

    for (i = 0; i < n; i++)
        a[i] = b[i] = i * 1.0;

    sum = 0.0;
    /* Создание множества параллельных процессов и распараллеливание
    * цикла по виткам. При выходе из цикла все значения переменной sum
    * суммируются по всем процессам. */
#pragma omp parallel for reduction(+:sum)
    for (i = 0; i < n; i++)
        sum = sum + (a[i] * b[i]);
    /* Главный процесс выводит на экран значение sum */
    printf(" Sum = %f\n", sum);
}