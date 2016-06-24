#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "matrix.h"

/*-------------- struct matrix *new_matrix() --------------
Inputs:  int rows
         int cols 
Returns: 

Once allocated, access the matrix as follows:
m->m[r][c]=something;
if (m->lastcol)...
*/
struct matrix *new_matrix(int rows, int cols) {
  double **tmp;
  int i;
  struct matrix *m;
  tmp = (double **)malloc(rows * sizeof(double *));
  for (i=0;i<rows;i++) {
    tmp[i]=(double *)malloc(cols * sizeof(double));
  }
  m=(struct matrix *)malloc(sizeof(struct matrix));
  m->m=tmp;
  m->rows = rows;
  m->cols = cols;
  m->lastcol = 0;
  return m;
}


/*-------------- void free_matrix() --------------
Inputs:  struct matrix *m 
Returns: 

1. free individual rows
2. free array holding row pointers
3. free actual matrix
*/
void free_matrix(struct matrix *m) {
  int i;
  for (i=0;i<m->rows;i++) {
      free(m->m[i]);
    }
  free(m->m);
  free(m);
}


/*======== void grow_matrix() ==========
Inputs:  struct matrix *m
         int newcols 
Returns: 

Reallocates the memory for m->m such that it now has
newcols number of collumns
====================*/
void grow_matrix(struct matrix *m, int newcols) {  
  int i;
  for (i=0;i<m->rows;i++) {
      m->m[i] = realloc(m->m[i],newcols*sizeof(double));
  }
  m->cols = newcols;
}


/*-------------- void print_matrix() --------------
Inputs:  struct matrix *m 
Returns: 

print the matrix
*/
void print_matrix(struct matrix *m) {
  int r,c;
  for (r=0;r<m->rows;r++){
    for (c=0;c<m->cols;c++){
      printf("%f ",m->m[r][c]);
    }
    printf("\n");
  }
}

/*-------------- void ident() --------------
Inputs:  struct matrix *m <-- assumes m is a square matrix
Returns: 

turns m in to an identity matrix
*/
void ident(struct matrix *m) {
  int r,c;
  for (r=0;r<4;r++){
    for (c=0;c<4;c++){
      if (r==c)
	m->m[r][c]=1;
      else
	m->m[r][c]=0;
    }
  }
}


/*-------------- void scalar_mult() --------------
Inputs:  double x
         struct matrix *m 
Returns: 

multiply each element of m by x
*/
void scalar_mult(double x, struct matrix *m) {
  int r,c;
  for (r=0;r<4;r++){
    for (c=0;c<4;c++){
      m->m[r][c]*=x;
    }
  }
}


/*-------------- void matrix_mult() --------------
Inputs:  struct matrix *a
         struct matrix *b 
Assuming that a has the same number of rows as b,
therefore the resultant matrix will be the same size as b
Returns: 

a*b -> b
*/
void matrix_mult(struct matrix *a, struct matrix *b) {
  int ar, ac_br, bc;
  double sum;
  struct matrix* result = new_matrix(a->rows,b->cols);
  for (ar=0;ar<a->rows;ar++){
    for (bc=0;bc<b->cols;bc++){
      sum=0.0;
      for(ac_br=0;ac_br<a->cols;ac_br++){
	sum += a->m[ar][ac_br]*b->m[ac_br][bc];
	result->m[ar][bc]=sum;
      }
    }
  }
  copy_matrix(result,b);
  free_matrix(result);
}


/*-------------- void copy_matrix() --------------
Inputs:  struct matrix *a
         struct matrix *b 
Returns: 

copy matrix a to matrix b
*/
void copy_matrix(struct matrix *a, struct matrix *b) {
  int r, c;
  for (r=0; r < a->rows; r++) 
    for (c=0; c < a->cols; c++)  
      b->m[r][c] = a->m[r][c];  
}

/*======== struct matrix * make_translate() ==========
Inputs:  int x
         int y
         int z 
Returns: The translation matrix created using x, y and z 
as the translation offsets.
====================*/
struct matrix * make_translate(double x, double y, double z) {
  struct matrix* trans = new_matrix(4,4);
  ident(trans);
  trans->m[0][3]=x;
  trans->m[1][3]=y;
  trans->m[2][3]=z;
  return trans;
}

/*======== struct matrix * make_scale() ==========
Inputs:  int x
         int y
         int z 
Returns: The translation matrix creates using x, y and z
as the scale factors
====================*/
struct matrix * make_scale(double x, double y, double z) {
  struct matrix* scale = new_matrix(4,4);
  ident(scale);
  scale->m[0][0]=x;
  scale->m[1][1]=y;
  scale->m[2][2]=z;
  return scale;
}

/*======== struct matrix * make_rotX() ==========
Inputs:  double theta

Returns: The rotation matrix created using theta as the 
angle of rotation and X as the axis of rotation.
====================*/
struct matrix * make_rotX(double theta) {
  theta/=180.0/M_PI;
  struct matrix* rotX = new_matrix(4,4);
  ident(rotX);
  rotX->m[1][1]=rotX->m[2][2]=cos(theta);
  rotX->m[2][1]=sin(theta);
  rotX->m[1][2]=-sin(theta);
  return rotX;  
}

/*======== struct matrix * make_rotY() ==========
Inputs:  double theta

Returns: The rotation matrix created using theta as the 
angle of rotation and Y as the axis of rotation.
====================*/
struct matrix * make_rotY(double theta) {
  theta/=180.0/M_PI;
  struct matrix* rotY = new_matrix(4,4);
  ident(rotY);
  rotY->m[0][0]=rotY->m[2][2]=cos(theta);
  rotY->m[2][0]=sin(theta);
  rotY->m[0][2]=-sin(theta);
  return rotY;
}

/*======== struct matrix * make_rotZ() ==========
Inputs:  double theta

Returns: The rotation matrix created using theta as the 
angle of rotation and Z as the axis of rotation.
====================*/
struct matrix * make_rotZ(double theta) {
  theta/=180.0/M_PI;
  struct matrix* rotZ = new_matrix(4,4);
  ident(rotZ);
  rotZ->m[0][0]=rotZ->m[1][1]=cos(theta);
  rotZ->m[1][0]=sin(theta);
  rotZ->m[0][1]=-sin(theta);
  return rotZ;  
}
