#include <omp.h>
#include <stdio.h>
#include <chrono>

#define M 3

int main()
{
    float A[M][M], B[M][M], C[M][M];
    int i, j, k;

    // Инициализация данных
    for (i = 0; i < M; i++)
    {
        for (j = 0; j < M; j++)
        {
            A[i][j] = i + 1;
            B[i][j] = j + 1;
            C[i][j] = 0.0;
        }
    }

    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    omp_set_num_threads(6);

#pragma omp parallel for private(i, j, k)
    for (i = 0; i < M; i++)
    {
        for (j = 0; j < M; j++)
        {
            for (k = 0; k < M; k++)
            {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    printf("Matrix A:\n");
    for (i = 0; i < M; i++)
    {
        for (j = 0; j < M; j++)
        {
            printf("%.1f ", A[i][j]);
        }
        printf("\n");
    }

    printf("\nMatrix B:\n");
    for (i = 0; i < M; i++)
    {
        for (j = 0; j < M; j++)
        {
            printf("%.1f ", B[i][j]);
        }
        printf("\n");
    }

    printf("\nResult Matrix C:\n");
    for (i = 0; i < M; i++)
    {
        for (j = 0; j < M; j++)
        {
            printf("%.1f ", C[i][j]);
        }
        printf("\n");
    }

    printf("Time taken: %lld milliseconds\n", std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count());

    return 0;
}
