#include <stdio.h>
#include <stdlib.h>

int main(){
  printf("%lf\n",0.0/0.0);
  if (-0.0/0.0 < 0){
    printf("BYE\n");
  }else{
    printf("HI\n");
  }
}
