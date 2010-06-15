#include <stdio.h>
#include <stdlib.h>
#include <tgmath.h>

#include <gsl/gsl_math.h>
#include <gsl/gsl_const_num.h>

#include <mpi.h>

#include "utils.h"

int main ( int argc, char **argv ) {

  int rank, size;
  MPI_Status status;
 
  MPI_Init( &argc, &argv );

  MPI_Comm_rank( MPI_COMM_WORLD, &rank );
  MPI_Comm_size( MPI_COMM_WORLD, &size );

  printf( "I am process %d of %d\n", rank, size );

  // MPI_Reduce()
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

  // MPI_Barrier()
  MPI_Barrier( MPI_COMM_WORLD );

  if (rank == 0) {
    printf("total is %d\n", total);
  }

  // MPI_Send()
  if ( rank < size-1 ) {
    MPI_Send(
      &rank,
      1,                  // count
      MPI_INT,
      rank+1,             // rank of destination
      0,                  // tag
      MPI_COMM_WORLD
    );
  }

  // MPI_Recv()
  if ( rank > 0 ) {
    int received_data;
    MPI_Recv(
      &received_data,
      1,                  // count
      MPI_INT,
      rank-1,             // rank of source
      0,                  // tag
      MPI_COMM_WORLD,
      &status
    );
    printf("my rank is %d and  I received data from process %d\n", rank, received_data);
  }

  MPI_Barrier( MPI_COMM_WORLD );

  // One-Pointed FDTD
  long double fdtd_array[10] = {0};
  long double my_point = 0;
  long double prev, next;

  for ( int time = 0; time<20000; time++ ) {

    switch (rank) {
      case 0:
        my_point = sin( (long double) time * PI / 180.0 );
        MPI_Send( &my_point, 1, MPI_LONG_DOUBLE, rank+1, 0, MPI_COMM_WORLD );
        break;

      case 9:
        MPI_Send( &my_point, 1, MPI_LONG_DOUBLE, rank-1, 0, MPI_COMM_WORLD );
        MPI_Recv( &prev, 1, MPI_LONG_DOUBLE, rank-1, 0, MPI_COMM_WORLD, &status );
        my_point = ( prev - 0 ) / 2.0L;
        break;

      default:
        MPI_Send( &my_point, 1, MPI_LONG_DOUBLE, rank+1, 0, MPI_COMM_WORLD );
        MPI_Send( &my_point, 1, MPI_LONG_DOUBLE, rank-1, 0, MPI_COMM_WORLD );

        MPI_Recv( &prev, 1, MPI_LONG_DOUBLE, rank-1, 0, MPI_COMM_WORLD, &status );
        MPI_Recv( &next, 1, MPI_LONG_DOUBLE, rank+1, 0, MPI_COMM_WORLD, &status );

        my_point = ( prev - next ) / 2.0L;
    
    }

    MPI_Barrier( MPI_COMM_WORLD );

    MPI_Gather( &my_point, 1, MPI_LONG_DOUBLE, fdtd_array, 1, MPI_LONG_DOUBLE, 0, MPI_COMM_WORLD );

    #ifdef DEBUG
    if ( rank == 0 ) {
      printf( "timestep %d => ", time );
      array_inspect_ld( fdtd_array, 10 );
      printf("\n");
    }
    #endif

  }

  MPI_Barrier( MPI_COMM_WORLD );

  MPI_Finalize();

  return 0;
}
