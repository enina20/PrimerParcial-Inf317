#include <iostream>
#include <mpi.h>

int main(int argc, char **argv) {
    int rank, size;

    // Inicializar MPI
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int number = 4; // Número para calcular el factorial
    int local_start, local_end;
    long long local_fact = 1, global_fact = 1;

    // Dividir el rango de números entre los procesos
    local_start = rank * (number / size) + 1;
    local_end = (rank == size - 1) ? number : (rank + 1) * (number / size);

    // Calcular el factorial parcial en cada proceso
    for (int i = local_start; i <= local_end; i++) {
        local_fact *= i;
    }

    // Recolectar los factoriales parciales y multiplicarlos
    MPI_Reduce(&local_fact, &global_fact, 1, MPI_LONG_LONG, MPI_PROD, 0, MPI_COMM_WORLD);

    // El proceso raíz (rank 0) imprime el resultado
    if (rank == 0) {
        std::cout << "El factorial de " << number << " es " << global_fact << std::endl;
    }

    // Finalizar MPI
    MPI_Finalize();
    return 0;
}
