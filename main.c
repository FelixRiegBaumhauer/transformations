#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ml6.h"
#include "display.h"
#include "draw.h"
#include "matrix.h"
#include "parser.h"

int main(int argc, char **argv) {

  screen s;
  struct matrix * edges;
  struct matrix * transform;

  edges = new_matrix(4, 4);
  transform = new_matrix(4, 4);

  color c;
  clear_screen(s); 
  c.red = MAX_COLOR;
  c.green = MAX_COLOR;
  c.blue = MAX_COLOR;

  //x y
  add_edge(edges, 100, 100, 0, 200, 100, 0);
  add_edge(edges, 200, 100, 0, 200, 200, 0);
  add_edge(edges, 200, 200, 0, 100, 200, 0);
  add_edge(edges, 100, 200, 0, 100, 100, 0);

  add_edge(edges, 100, 100, 100, 200, 100, 100);
  add_edge(edges, 200, 100, 100, 200, 200, 100);
  add_edge(edges, 200, 200, 100, 100, 200, 100);
  add_edge(edges, 100, 200, 100, 100, 100, 100);

  add_edge(edges, 100, 100, 0, 100, 100, 100);
  add_edge(edges, 200, 100, 0, 200, 100, 100);
  add_edge(edges, 200, 200, 0, 200, 200, 100);
  add_edge(edges, 100, 200, 0, 100, 200, 100);

  
  
  transform = make_rotY(1);
  matrix_mult(transform, edges);

  transform = make_rotX(1);
  matrix_mult(transform, edges);
  
  draw_lines(edges, s, c);

  display(s);
  
  /*
  if ( argc == 2 )
    parse_file( argv[1], transform, edges, s );
  else
    parse_file( "stdin", transform, edges, s );
  */
  
  free_matrix( edges );
  free_matrix( transform );
} 
