#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "toDoList.h"

int main (int argc, const char * argv[])
{
  	TYPE task1, task2, task3, task4, task5, task6, task7, task8, task9, task10;
	DynArr mainList;
	int i;
	initDynArr(&mainList, 10);

	/* create tasks */
	task1 = createTask(9, "task 1");
	task2 = createTask(3, "task 2");
	task3 = createTask(2, "task 3");
	task4 = createTask(4, "task 4");
	task5 = createTask(5, "task 5");
	task6 = createTask(7, "task 6");
	task7 = createTask(8, "task 7");
	task8 = createTask(6, "task 8");
	task9 = createTask(1, "task 9");
	task10 = createTask(0, "task 10");
	
	/* add tasks to the dynamic array */
	addHeap(&mainList, task1);
	addHeap(&mainList, task2);
	addHeap(&mainList, task3);
	addHeap(&mainList, task4);
	addHeap(&mainList, task5);
	addHeap(&mainList, task6);
	addHeap(&mainList, task7);
	addHeap(&mainList, task8);
	addHeap(&mainList, task9);
	addHeap(&mainList, task10);

	/* sort tasks */
	sortHeap(&mainList);

	/* print sorted tasks from the dynamic array */
	for (i = 0; i < mainList.size; i++)
	{
	  	printf("%d\n", mainList.data[i].priority);
	}

	return 0;
}
