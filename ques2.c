#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
 
int main(int argc, char* argv[])
{
    MPI_Init(&argc, &argv);
 
    int size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    if(size != 4)
    {
        printf("Terminated..!!\n");
        MPI_Abort(MPI_COMM_WORLD, EXIT_FAILURE);
    }
 
    
    int root_rank = 0;
 
   
    int my_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
 
    
    int my_value = my_rank * 100;
    printf("Process : %d,Value : %d.\n", my_rank, my_value);
 
    if(my_rank == root_rank)
    {
        int buffer[4];
        MPI_Gather(&my_value, 1, MPI_INT, buffer, 1, MPI_INT, root_rank, MPI_COMM_WORLD);
        printf("Values collected on Process %d: %d, %d, %d, %d.\n", my_rank, buffer[0], buffer[1], buffer[2], buffer[3]);
    }
    else
    {
        MPI_Gather(&my_value, 1, MPI_INT, NULL, 0, MPI_INT, root_rank, MPI_COMM_WORLD);
    }
 
    MPI_Finalize();
 
    return EXIT_SUCCESS;
}

