#include "mpi.h"
#include <iostream>
#include <vector>

#define N 10

int main(int argc, char** argv)
{
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    std::vector<float> matrix(N * N, rank + 1);
    std::vector<float> vector(N, rank + 1);
    std::vector<float> result(N, 0);

    MPI_Status status;

    // Умножение части матрицы на вектор
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            result[i] += matrix[i * N + j] * vector[j];
        }
    }

    // Передача результата по кольцевой топологии
    int left = (rank - 1 + size) % size;
    int right = (rank + 1) % size;

    for (int i = 0; i < size; i++)
    {
        if (i % 2 == 0)
        {
            MPI_Send(&result[0], N, MPI_FLOAT, right, 0, MPI_COMM_WORLD);
            MPI_Recv(&result[0], N, MPI_FLOAT, left, 0, MPI_COMM_WORLD, &status);
        }
        else
        {
            MPI_Recv(&result[0], N, MPI_FLOAT, left, 0, MPI_COMM_WORLD, &status);
            MPI_Send(&result[0], N, MPI_FLOAT, right, 0, MPI_COMM_WORLD);
        }
    }

    // Вывод результата
    if (rank == 0)
    {
        std::cout << "Matrix:\n";
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                std::cout << matrix[i * N + j] << " ";
            }
            std::cout << std::endl;
        }

        std::cout << "\nVector:\n";
        for (int i = 0; i < N; i++)
        {
            std::cout << vector[i] << " ";
        }
        std::cout << std::endl;

        std::cout << "\nResult:\n";
        for (int i = 0; i < N; i++)
        {
            std::cout << result[i] << " ";
        }
        std::cout << std::endl;
    }

    MPI_Finalize();

    return 0;
}