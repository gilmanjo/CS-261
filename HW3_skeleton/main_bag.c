#include "listbag.h"
#include <malloc.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

/*Function to get number of milliseconds elapsed since program started execution*/
double getMilliseconds() {
   return 1000.0 * clock() / CLOCKS_PER_SEC;
}

int main(int argc, char* argv[]){
  if(argc==2)
    {
      struct bag* b = (struct bag*)malloc(sizeof(struct bag));/*Create new bag*/
      initBag(b);/*Initialize*/
      char* s=argv[1];
      int n = atoi(s);/*number of elements to add*/
      int i;
      double n1 = getMilliseconds();
      for( i = 0 ; i < n; ++i) {
	     addToBag(b, (TYPE)i);/*Add elements*/
      }
      printf("%d\n", bagContains(b, (TYPE)149));
      removeFromBag(b, (TYPE)149);
      printf("%d\n", bagContains(b, (TYPE)149));
    }
  else
    printf("Please enter the number of elements to add.\n");

  return 0;

}
