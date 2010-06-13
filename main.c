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
  
  MPI_Finalize();

  return 0;
}