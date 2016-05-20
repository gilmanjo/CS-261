/* CS261- HW1 - Program2.c*/
/* Name:  Jordan Gilman
 * Date:  4/01/2016
 * Solution description:  Here I assume that we are intended to pass
 x, y, and z by value into the function 'foo'.  By doing that, we
 essentially find the exclusive difference in memory location between 
 x and y.  srand is used to set a RNG seed based on the current time.
 */
 
#include <stdio.h>
#include <stdlib.h>

int foo(int* a, int* b, int c){
    *a = *a + 1;/* Increment a */
    
    *b = *b + 1;/* Decrement  b */

    c = *a - *b;/* Assign a-b to c */

    return c;/* Return c */
}

int main(){
      /* Declare three integers x,y and z and initialize them randomly to values in [0,10] */
    srand((unsigned) time(NULL));
    int x = rand() % 11;
    int y = rand() % 11;
    int z = rand() % 11;
    
    printf("x = %d, y = %d, z = %d\n",x,y,z);  /* Print the values of x, y and z */
    
    int value = foo(&x, &y, z);/* Call foo() appropriately, passing x,y,z as parameters */
    
    printf("x = %d, y = %d, z = %d\n",x,y,z);  /* Print the values of x, y and z */
    
    printf("value = %d",value);/* Print the value returned by foo */
 
    /* Is the return value different than the value of z?  Why? */
    /*  Yes the values are different because we passed all of the arguments
    by value and the first two parameters of the function 'foo' are
    pointers. */
    return 0;
}
    
    
