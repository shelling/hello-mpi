void array_inspect_ld ( const long double * array, const int length ) {
  printf( "[ " );
  for ( int i=0; i<length; i++ ) {
    printf("%LF ", array[i]);
  }
  printf("]");
}
