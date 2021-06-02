#include <stdio.h>
#include <string.h>
#include <mpi.h>
#include <stdlib.h>


int main(void){

    int comm_sz; // numero de procesos
    int my_rank;

    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
    MPI_Comm_rank( MPI_COMM_WORLD , &my_rank);

    int arr_size = 20;
    if(arr_size % comm_sz != 0){
        printf("El tamaño del array no es divisible entre el número de procesos");
        MPI_Finalize();
        return 1;
    }
    int main_arr[20] = {
        1,2,3,8,1,
        3,1,1,4,1,
        1,1,4,1,1,
        8,1,7,4,1
    };

    int sub_arr_size = arr_size/comm_sz;

    

    int local_sum = 0;
    for(int i=0; i<sub_arr_size; i++){
        int pos = (my_rank*sub_arr_size)+i;
        local_sum += main_arr[pos];
    }
    int total_sum = 0;
    int total_sum_all = 0;
    MPI_Reduce(&local_sum, &total_sum, 1,  MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    MPI_Allreduce(&local_sum, &total_sum_all, 1,  MPI_INT, MPI_SUM, MPI_COMM_WORLD);


    if(my_rank == 0){

        int test_res = 0;

        for(int i=0; i<arr_size; i++){
            int temp = main_arr[i];
            test_res += temp;
        }

        printf("\nResultado reduce: %d", total_sum);
        printf("\nResultado reduce all: %d", total_sum);
        printf("\nResultado NO paralelo %d\n", test_res);
    } 

    MPI_Finalize();
    return 0;
}
