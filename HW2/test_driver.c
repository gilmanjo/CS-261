#include <stdio.h>
#include <stdlib.h>
#include "dynArray.h"

int main() {
	printf("test");

	DynArr *testDy = newDynArr(1);
	addDynArr(testDy, 1);
	addDynArr(testDy, 2);
	addDynArr(testDy, 3);
	addDynArr(testDy, 4);
	addDynArr(testDy, 5);
	addDynArr(testDy, 100);
	int i = getDynArr(testDy, 0);
	printf("\n%d\n", i);
	swapDynArr(testDy, 5, 0);
	i = getDynArr(testDy, 0);
	printf("\n%d\n", i);

	removeAtDynArr(testDy, 0);
	i = getDynArr(testDy, 0);
	printf("\n%d\n", i);

	deleteDynArr(testDy);

	return 0;
}