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

    int arr_size = 1000;
    if(arr_size % comm_sz != 0){
        printf("No se puede hacer el proceso, el tamaño del array no es divisible");
        MPI_Finalize();
        return 1;
    }

    int sub_arr_size = arr_size/comm_sz;
    int sub_arr[sub_arr_size];

    if(my_rank == 0){

        int main_arr[arr_size];
        int test_res = 0;

        for(int i=0; i<arr_size; i++){
            int temp = rand();
            main_arr[i] = temp;
            test_res += temp;
        }

        printf("1");
        for(int i=1; i<comm_sz; i++){

            for(int j=0; j<sub_arr_size; j++){
                int pos = (i*sub_arr_size)+j;
                sub_arr[j]=main_arr[pos];
            }

            MPI_Send(&sub_arr, sub_arr_size, MPI_INT, i, 0, MPI_COMM_WORLD);
        }
        printf("2");

        int total_sum = 0;

        for(int k=0; k<sub_arr_size; k++){
            total_sum += main_arr[k];
        }
        printf("3");
        for(int i=1; i<comm_sz; i++){
            int process_sum;
            MPI_Recv(&process_sum, 1, MPI_INT, i, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            total_sum += process_sum;
        }

        printf("\nParalelo: %d", total_sum);
        printf("\nSin paralelizar: %d\n", test_res);
    } else {

        printf("4");

        MPI_Recv(&sub_arr, sub_arr_size, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        printf("5");
        int temp_sum = 0;
        for(int i=0; i<sub_arr_size; i++){
            temp_sum += sub_arr[i];
        }
        MPI_Send(&temp_sum, 1, MPI_INT, 0, 1, MPI_COMM_WORLD);
        printf("6");
        
    }

    MPI_Finalize();
    return 0;
}
