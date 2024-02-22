#include<omp.h>
#include<stdio.h>

int main()
{
    int size, rank;
    /* Создание множества параллельных процессов и в каждом из них задаются
    * свои приватные переменные size и rank */
#pragma omp parallel private(size, rank)
    {
        /* Каждый процесс находит свой порядковый номер и выводит его на экран */
        rank = omp_get_thread_num();
        printf("Hello World from thread = %d\n", rank);
        /* Главный процесс - master выводит на экран количество процессов */
        if (rank == 0)
        {
            size = omp_get_num_threads();
            printf("Number of threads = %d\n", size);
        }
    }
}