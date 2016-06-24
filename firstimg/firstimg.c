#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(){

  FILE* f = fopen("first.ppm","w");
  fprintf(f,"P3 500 500 255 ");
  
  int x,y;
  int r,g,b = 0;
  
  for (x=0;x<500;x++){
    for (y=0;y<500;y++){
      r = (x*x-x+1)%256;
      g = (x+y)%256;
      b = (x*x + y*y + g)%256;
      fprintf(f,"%d %d %d ",r,g,b);
      
    }
  }
  
  fclose(f);
  
}
