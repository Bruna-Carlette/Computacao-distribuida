void probing_process(int &int_sum, float &float_sum) {
  MPI_Status status;
  MPI_Probe(MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);

  int tag = status.MPI_TAG;
  int source = status.MPI_SOURCE;

  std::cout << "Received a message from process " << source << " with tag " << tag << std::endl;


  if (tag == 0) {
    int received_int;
    MPI_Recv(&received_int, 1, MPI_INT, source, tag, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    int_sum += received_int;
  } else if (tag == 1) {
    float received_float;
    MPI_Recv(&received_float, 1, MPI_FLOAT, source, tag, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    float_sum += received_float;
  }
}