#include <stdio.h>
#include <stdlib.h>

#include "ml6.h"
#include "display.h"
#include "draw.h"

//Insert your line algorithm here
void draw_line(int x0, int y0, int x1, int y1, screen s, color c) {
  int swap;
  if (x0>x1){
    swap=x0; x0=x1; x1=swap;
    swap=y0; y0=y1; y1=swap;
  }
  int A,B;
  int d;
  A = y1-y0; B = x0-x1;// C =  y0 - A / B * x0 * B;
  float temp = (float)A / -(float)B;
  //q2,6
  if (temp >= 1){
    d = A + 2 * B;
    A*=2;B*=2;
    while (y0 < y1){
      plot(s,c,x0,y0);
      if (d < 0){
	x0+=1;
	d+=A;
      }
      y0+=1;
      d+=B;
    }    
  }
  //q1,5
  else if (temp >= 0){
    d = 2 * A + B;
    A*=2;B*=2;
    while (x0 < x1){
      plot(s,c,x0,y0);
      if (d > 0){
	y0+=1;
	d+=B;
      }
      x0+=1;
      d+=A;
    }
  }
  //q4,8
  else if (temp >= -1){
    d = 2 * A + B;
    A*=2;B*=2;
    while (x0 < x1){
      plot(s,c,x0,y0);
      if (d < 0){
	y0-=1;
	d-=B;
      }
      x0+=1;
      d+=A;
    }
  }
  //q3,7
  else{
    d = A + 2 * B;
    A*=2;B*=2;
    while (y0 > y1){
      plot(s,c,x0,y0);
      if (d > 0){
	x0+=1;
	d+=A;
      }
      y0-=1;
      d-=B;
    }    
  }
}

