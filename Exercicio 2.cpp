#include <iostream>
#include <mpi.h>
#include <cstdlib>

int main(int argc, char **argv) {
  MPI_Init(&argc, &argv);

  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  int local_value;
  local_value = atoi(argv[1]);

  int other_value;
  if (rank == 0) {
    MPI_Send(&local_value, 1, MPI_INT, 1, 0, MPI_COMM_WORLD); 
    MPI_Recv(&other_value, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    std::cout << local_value + other_value << std::endl;
  }
  else {
    MPI_Recv(&other_value, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    MPI_Send(&local_value, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
    std::cout << local_value * other_value << std::endl;
  }  
  MPI_Finalize();
  
  return 0;
}
