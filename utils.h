#ifndef PI
#define PI 3.1415926535897932384626433832795L
#endif

void array_inspect_ld ( const long double * array, const int length ) {
  printf( "[ " );
  for ( int i=0; i<length; i++ ) {
    printf("%LF ", array[i]);
  }
  printf("]");
}
