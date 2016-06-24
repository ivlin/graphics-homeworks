#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ml6.h"
#include "display.h"
#include "draw.h"
#include "matrix.h"
#include "parser.h"
#include "stack.h"

int main( int argc, char** argv ) {

  screen s;
  struct matrix *edges;
  struct matrix *transform;
  struct stack *stack;

  stack = new_stack();
  edges = new_matrix(4, 4);
  transform = new_matrix(4, 4);

  if ( argc == 2 )
    parse_file( argv[1], transform, edges, s, stack);
  else
    parse_file( "stdin", transform, edges, s, stack);

  free_stack( stack );
  free_matrix( transform );
  free_matrix( edges );
}
