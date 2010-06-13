#include <stdio.h>
#include <stdlib.h>
#include <tgmath.h>
#include <mpi.h>

int main ( int argc, char **argv ) {

  int rank, size;
  MPI_Status status;

  char message[20];

  MPI_Init( &argc, &argv );

  MPI_Comm_rank( MPI_COMM_WORLD, &rank );
  MPI_Comm_size( MPI_COMM_WORLD, &size );

  printf( "I am process %d of %d\n", rank, size );

  int total;
  MPI_Reduce( 
    &rank,
    &total,
    1,
    MPI_INT,
    MPI_SUM,
    0,
    MPI_COMM_WORLD
  );

  if (rank == 0) {
    printf("total is %d\n", total);
  }

  if ( rank < size-1 ) {
    MPI_Send(
      &rank,
      1,
      MPI_INT,
      rank+1,            // rank of process to receive data
      0,
      MPI_COMM_WORLD
    );
  }

  if ( rank > 0 ) {
    int received_data;
    MPI_Recv(
      &received_data,
      1,
      MPI_INT,
      rank-1,
      0,
      MPI_COMM_WORLD,
      &status
    );
    printf("my rank is %d and  I received data from process %d\n", rank, received_data);
  }

  MPI_Finalize();

  return 0;
}
