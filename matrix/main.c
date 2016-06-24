#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ml6.h"
#include "display.h"
#include "draw.h"
#include "matrix.h"
#include <math.h>

int main() {
  screen s; color c;
  c.red=0;
  c.blue=255;
  c.green=140;
  
  struct matrix *edges = new_matrix(4, 0);
  add_edge(edges,100,100.0,0.0,400.0,100.0,0.0);
  add_edge(edges,100,100.0,0.0,100.0,400.0,0.0);
  add_edge(edges,400,400.0,0.0,400.0,100.0,0.0);
  add_edge(edges,400,400.0,0.0,100.0,400.0,0.0);
  
  struct matrix *transform = make_translate(10,1.0,0);
  struct matrix* scale = make_scale(0.95,0.95,0.0);
  struct matrix* rot1 = make_rotZ(0.1);
  struct matrix* rot2 = make_rotY(0.1);
  struct matrix* composite = new_matrix(4,4);
  ident(composite);
  matrix_mult(transform,composite);
  matrix_mult(scale,composite);
  matrix_mult(rot1,composite);
  matrix_mult(rot2,composite);
  
  int i;
  for (i=0;i<50;i++){ 
    matrix_mult(rot1,composite);
    draw_lines(edges,s,c);
    c.red=(c.red+5)%256;
    c.green=(c.green-5)%256;
    matrix_mult(composite,edges);
  }

  free_matrix(rot1);
  free_matrix(rot2);
  free_matrix(scale);
  free_matrix(transform);
  free_matrix(composite);
  free_matrix(edges);
  
  display(s);
  save_extension(s,"matrix.png");
}  
