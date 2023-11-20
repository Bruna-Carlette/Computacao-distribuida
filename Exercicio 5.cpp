#include <iostream>
#include <iomanip>
#include <mpi.h>

int main(int argc, char **argv) {
  MPI_Init(&argc, &argv);

  int rank, size;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  int n_elements;
  double *buffer;
  if (rank == 0) {
    std::cin >> n_elements;
    buffer = new double[n_elements];
    
    for (int i=0; i < n_elements; ++i)
      std::cin >> buffer[i];
  }

  MPI_Bcast(&n_elements, 1, MPI_INT, 0, MPI_COMM_WORLD);

  if (rank != 0)
    buffer = new double[n_elements];

  MPI_Bcast(buffer, n_elements, MPI_DOUBLE, 0, MPI_COMM_WORLD);
  
  double sum = 0.0;

  for (int i = 0; i < n_elements; i++) {
    if (rank == 0) {
      sum += buffer[i];
    } else if (rank == 1 && buffer[i] > 0) {
      sum += buffer[i];
    } else if (rank == 2 && buffer[i] < 0) {
      sum += buffer[i];
    }
  }

  std::cout << std::setprecision(16) << sum << std::endl;
  
  MPI_Finalize();
  delete [] buffer;

  return 0;
}