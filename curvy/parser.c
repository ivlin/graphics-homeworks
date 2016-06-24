#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "ml6.h"
#include "display.h"
#include "draw.h"
#include "matrix.h"
#include "parser.h"


/*======== void parse_file () ==========
Inputs:   char * filename 
          struct matrix * transform, 
          struct matrix * pm,
          screen s
Returns: 

Goes through the file named filename and performs all of the actions listed in that file.
The file follows the following format:
     Every command is a single character that takes up a line
     Any command that requires arguments must have those arguments in the second line.
     The commands are as follows:
         line: add a line to the edge matrix - 
	    takes 6 arguemnts (x0, y0, z0, x1, y1, z1)
	 circle: add a circle to the edge matrix - 
	    takes 3 arguments (cx, cy, r)
	 hermite: add a hermite curve to the edge matrix -
	    takes 8 arguments (x0, y0, x1, y1, x2, y2, x3, y3)
	 bezier: add a bezier curve to the edge matrix -
	    takes 8 arguments (x0, y0, x1, y1, x2, y2, x3, y3)
	 ident: set the transform matrix to the identity matrix - 
	 scale: create a scale matrix, 
	    then multiply the transform matrix by the scale matrix - 
	    takes 3 arguments (sx, sy, sz)
	 translate: create a translation matrix, 
	    then multiply the transform matrix by the translation matrix - 
	    takes 3 arguments (tx, ty, tz)
	 xrotate: create an x-axis rotation matrix,
	    then multiply the transform matrix by the rotation matrix -
	    takes 1 argument (theta)
	 yrotate: create an y-axis rotation matrix,
	    then multiply the transform matrix by the rotation matrix -
	    takes 1 argument (theta)
	 zrotate: create an z-axis rotation matrix,
	    then multiply the transform matrix by the rotation matrix -
	    takes 1 argument (theta)
	 apply: apply the current transformation matrix to the 
	    edge matrix
	 display: draw the lines of the edge matrix to the screen
	    display the screen
	 save: draw the lines of the edge matrix to the screen
	    save the screen to a file -
	    takes 1 argument (file name)
	 quit: end parsing

See the file script for an example of the file format


IMPORTANT MATH NOTE:
the trig functions int math.h use radian mesure, but us normal
humans use degrees, so the file will contain degrees for rotations,
be sure to conver those degrees to radians (M_PI is the constant
for PI)
====================*/
void parse_file ( char * filename, 
                  struct matrix * transform, 
                  struct matrix * pm,
                  screen s) {
  FILE *f;
  char line[256];
  char next[256];
  char *next_arg;
  color c;
  c.red=255;c.blue=255;c.green=25;
  double args[52];
  double DEFAULT_STEP=0.01;
  clear_screen(s);
  
  if ( strcmp(filename, "stdin") == 0 ) 
    f = stdin;
  else
    f = fopen(filename, "r");
  
  while ( fgets(line, 255, f) != NULL ) {  
    line[strlen(line)-1]='\0';
    if (strcmp(line,"apply")==0){
      matrix_mult(transform,pm);
    }
    else if (strcmp(line,"display")==0){
      draw_lines(pm,s,c);
      display(s);
    }
    else if (strcmp(line,"quit")==0){
      exit(0);
    }
    else if (strcmp(line,"ident")==0){
      ident(transform);
    }
    else{
      fgets(next,255,f);
      next[strlen(next)-1]='\0';
      next_arg=next;
      int i = 0;
      while (next_arg != 0){
	args[i]=strtod(strsep(&next_arg," "),NULL);
	i++;
      }
      if (strcmp(line,"save")==0){
	fgets(next,255,f);
	save_extension(s,next);
      }
    }
    if (strcmp(line,"line")==0){
      add_edge(pm,args[0],args[1],args[2],args[3],args[4],args[5]);
    }
    if (strcmp(line,"circle")==0){
      add_circle(pm,args[0],args[1],args[2],DEFAULT_STEP);
    }
    if (strcmp(line,"hermite")==0){
      add_curve(pm,args[0],args[1],args[4],args[5],args[2]-args[0],args[3]-args[1],args[6]-args[4],args[7]-args[5],DEFAULT_STEP,HERMITE_MODE);
    }
    if (strcmp(line,"bezier")==0){
      add_curve(pm,args[0],args[1],args[2],args[3],args[4],args[5],args[6],args[7],DEFAULT_STEP,BEZIER_MODE);
    }
    if (strcmp(line,"scale")==0){
      matrix_mult(make_scale(args[0],args[1],args[2]),transform);
    }
    if (strcmp(line,"translate")==0){
      matrix_mult(make_translate(args[0],args[1],args[2]),transform);
    }
    if (strcmp(line,"xrotate")==0){
      matrix_mult(make_rotX(M_PI*args[0]/180.0),transform);
    }
    if (strcmp(line,"yrotate")==0){
      matrix_mult(make_rotY(M_PI*args[0]/180.0),transform);
    }
    if (strcmp(line,"zrotate")==0){
      matrix_mult(make_rotZ(M_PI*args[0]/180.0),transform);
    }   
    printf(":%s:\n",line);  
  }
}
