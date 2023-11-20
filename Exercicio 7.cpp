void compute(int total_count, int my_count, float my_points[][3]) {

  int rank, size;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  float local_sum[3] = {0.0f, 0.0f, 0.0f};
  for (int i = 0; i < my_count; ++i) {
    for (int j = 0; j < 3; ++j) {
      local_sum[j] += my_points[i][j];
    }
  }

  float barycentre[3];
  MPI_Allreduce(local_sum, barycentre, 3, MPI_FLOAT, MPI_SUM, MPI_COMM_WORLD);
  
  for (int i = 0; i < 3; ++i) {
    barycentre[i] /= total_count;
  }

  for (int i=0; i < my_count; ++i) {
    float dist = 0.0f;

    for (int j = 0; j < 3; ++j) {
        dist += std::pow(my_points[i][j] - barycentre[j], 2);
    }
    dist = std::sqrt(dist);

    std::cout << rank << " " << dist << std::endl;
  }
}