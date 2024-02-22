﻿#include <omp.h>
#include <stdio.h>
#include <chrono>
#define M 10

int main()
{
    float A[M][M], b[M], c[M];
    int i, j, rank;

    // Инициализация данных
    for (i = 0; i < M; i++)
    {
        for (j = 0; j < M; j++)
            A[i][j] = (j + 1) * 1.0;
        b[i] = 1.0 * (i + 1);
        c[i] = 0.0;
    }

    printf("Вывод значений матрицы A и вектора b на экран\n");

    for (i = 0; i < M; i++)
    {
        printf("A[%d]= ", i);
        for (j = 0; j < M; j++)
            printf("%.1f ", A[i][j]);
        printf("b[%d]= %.1f\n", i, b[i]);
    }

    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    omp_set_num_threads(2);

    // Создание параллельных процессов, каждый из которых вычисляет часть результатов
#pragma omp parallel shared(A, b, c) private(rank, i)
    {
        rank = omp_get_thread_num();
        // Распределение работы по виткам цикла между процессами
#pragma omp for private(j)
        for (i = 0; i < M; i++)
        {
            for (j = 0; j < M; j++)
                c[i] += A[i][j] * b[j];
            // Вывод результатов каждого процесса
#pragma omp critical
            {
                printf("rank= %d i= %d c[%d]=%.2f\n", rank, i, i, c[i]);
            }
        }
    }
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    printf("Time taken: %lld milliseconds\n", std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count());
    return 0;
}
