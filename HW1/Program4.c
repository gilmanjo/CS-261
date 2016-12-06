/* CS261- HW1 - Program4.c*/
/* Name:  Jordan Gilman
 * Date:  4/01/2016
 * Solution description:  I used the random function with a seed based on
 time to generate 20 random integers between 0 and 100.  My sorting algorithm
 is of quadratic complexity.  For each integer in the array, it checks whether
 the integer after is less than it.  If it is, it swaps them.  This runs one pass through the array per integer in the array.  That is, O(n^2).
 */
 
#include <stdio.h>

void sort(int *number, int n){
     /*Sort the given array number , of length n*/

	 int i;
	 for(i = 0; i < n; i++) {
	 	int j;
	   for(j = 0; j < n - 1; j++) {
	   	if(number[j] > number[j + 1]) {
	   		int temp = number[j + 1];
	   		number[j + 1] = number[j];
	   		number[j] = temp;
	   	}
	   }
	 }
}

int main(){
    /*Declare an integer n and assign it a value of 20.*/
    int n = 20;

    /*Allocate memory for an array of n integers using malloc.*/
    int *numbers = (int*) malloc(n*sizeof(int));

    /*Fill this array with random numbers, using rand().*/
    int i;
    srand((unsigned) time(NULL));

    for(i = 0; i < n; i++) {
    	numbers[i] = rand() % 101;
    }

    /*Print the contents of the array.*/
    printf("Unsorted:\n");
    for(i = 0; i < n; i++) {
    	printf("%d\n",numbers[i]);
    }

    /*Pass this array along with n to the sort() function of part a.*/
    sort(numbers, n);
    
    /*Print the contents of the array.*/    
    printf("Sorted:\n");
    for(i = 0; i < n; i++) {
    	printf("%d\n",numbers[i]);
    }

    return 0;
}
