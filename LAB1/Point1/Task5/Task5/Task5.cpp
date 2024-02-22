#include <omp.h>
#include<stdio.h>
#define M 10

int main()
{
    float A[M][M], b[M], c[M];
    int i, j, rank;
    /* Инициализация данных */
    for (i = 0; i < M; i++)
    {
        for (j = 0; j < M; j++)
            A[i][j] = (j + 1) * 1.0;
        b[i] = 1.0 * (i + 1);
        c[i] = 0.0;
    }

    printf("\VIVOD ZNACHENII MATRIX A I VEKTORA b NA EKRAN:\n");

    for (i = 0; i < M; i++)
    {
        printf(" A[%d]= ", i);
        for (j = 0; j < M; j++)
            printf("%.1f ", A[i][j]);
        printf(" b[%d]= %.1f\n", i, b[i]);
    }
    /* Создание множества параллельных процессов и в каждом из них задаются
    * свои приватные переменные rank и i*/
#pragma omp parallel shared(A,b,c) private(rank,i)
    {
        rank = omp_get_thread_num();
        /* Директива распараллеливания цикла по виткам */
#pragma omp for private(j)
        for (i = 0; i < M; i++)
        {
            for (j = 0; j < M; j++)
                c[i] += (A[i][j] * b[j]);
            /* Каждый процесс выводит свой порядковый номер, значение витка цикла и
            * значение результирующего вектора на каждом витке цикла и внутри
            * критической секции */
#pragma omp critical
            {
                printf(" rank= %d i= %d c[%d]=%.2f\n", rank, i, c[i]);
            }
        } /* Конец параллельного цикла */
    } /* Завершение параллельной конструкции */
}