int world_rank, world_size;
MPI_Comm custom_comm1, custom_comm2, custom_comm3, tmp;

void splitting() {
    int color;

    if (world_rank >= 0 && world_rank <= 3) {
        color = 1; 
        MPI_Comm_split(MPI_COMM_WORLD, color, world_rank, &custom_comm1);
    } else if (world_rank >= 4 && world_rank <= 6) {
        color = 2;
        MPI_Comm_split(MPI_COMM_WORLD, color, world_rank, &custom_comm2);
    } else {
        MPI_Comm_split(MPI_COMM_WORLD, MPI_UNDEFINED, world_rank, &tmp);
    }

    if (world_rank == 0 || world_rank == 4) {
        color = 3;
        MPI_Comm_split(MPI_COMM_WORLD, color, world_rank, &custom_comm3);
    } else {
        MPI_Comm_split(MPI_COMM_WORLD, MPI_UNDEFINED, world_rank, &tmp);
    }
}