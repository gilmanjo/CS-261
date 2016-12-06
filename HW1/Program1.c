/* CS261- HW1 - Program1.c */
/* Name:	Jordan Gilman
 * Date:	4/01/2016
 * Solution description:  Pretty basic.  *denotes a value the pointer
 points to.  & denotes the address of a value.  *& denotes the address 
 of a value a pointer points to.
 */
 
#include <stdio.h>
#include <stdlib.h>

void fooA(int* iptr){
     printf("%d\n",*iptr);/*Print the value of iptr*/
     
     printf("%p\n",&*iptr);/*Print the address pointed to by iptr*/
     
     printf("%p\n",&iptr);/*Print the address of iptr itself*/
}

int main(){
    
    int x = 22;/*declare an integer x*/
    
    printf("%p\n",&x);/*print the address of x*/
    
    fooA(&x);/*Call fooA() with the address of x*/
    
    printf("%d\n",x);/*print the value of x*/
    
    return 0;
}
