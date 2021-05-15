#include <stdio.h>
#include <mpi.h>

int main(void)
{
    int comm_sz;
    int my_rank;
    int global = 0;

    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    if (my_rank == 0){
        global = 20;
        printf("Valor de numero %d en el proceso %d \n", global, my_rank);
    }else{
        printf("Valor de numero %d \n", global);
    }
    MPI_Finalize();
    return 0;
}