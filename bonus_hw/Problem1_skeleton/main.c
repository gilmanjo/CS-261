#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include "avl.h"

/* find minimum-cost path */
/* Input: pointer to tree
          pointer to array that should store all node values from
                  root to leaf along the identified min-cost path, 
   Output: min-cost path length 
*/
int FindMinPath(struct AVLTree *tree, int *path)
{
	struct AVLnode * cur = tree->root;
	struct AVLnode * parents[100];

	/* Flags are used to keep track of whether a child tree has
	already been iterated through */
	int leftFlag[100];
	int rightFlag[100];

	/* Path variable to help keep track of the current path cost */
	int pathBuffer[100];
	int pathCost = 0;
	int leastPathCost = -1;

	/* Identical to AVL height, except */
	int tmpHeight = cur->height;


	int i = 1; /* counts the number of nodes along a path */
	int j;
	int k;

	/* printf("Height of tree: %d\n\n", tree->root->height); */

	/* Initialize flags */
	for(j = 0; j < 100; j++) {
		leftFlag[j] = 0;
		rightFlag[j] = 0;
	}

	while(cur != NULL) {
		/* printf("Node Value: %d\n", cur->val);
		printf("Height: %d\n", cur->height); */
		pathBuffer[i - 1] = cur->val;
		if(cur->left != NULL && leftFlag[tmpHeight] != 1) {
			parents[tmpHeight] = cur;
			leftFlag[tmpHeight] = 1;
			cur = cur->left;
			tmpHeight--;
			i++;
		}
		else if(cur->right != NULL && rightFlag[tmpHeight] != 1) {
			parents[tmpHeight] = cur;
			rightFlag[tmpHeight] = 1;
			cur = cur->right;
			tmpHeight--;
			i++;
		}

		else {
			/* Clear all flags at this level and below */
			if(cur == tree->root)
				break;

			/* Give the length of the most recent path */
			if(cur->right == NULL && cur->left == NULL) {
				pathCost = pathBuffer[0];
				for(j = 1; j < i; j++) 
					pathCost += abs(pathBuffer[j] - pathBuffer[j - 1]);

				/* printf("\tLatest path cost: %d\n", pathCost); */

				/* If this is the least cost path so far, copy it over */			
				if(leastPathCost == -1 || pathCost < leastPathCost) {
					for(j = 0; j < i; j++)
						path[j] = pathBuffer[j];
				leastPathCost = pathCost;
				}
				
				k = i + 1;
				/* for(j = 0; j < i; j++)
					printf("Path #%d: %d\n", j, path[j]); */
			}

			/* Reset flags under this node before returning up */
			for(j = 0; j <= tmpHeight; j++) {
				leftFlag[j] = 0;
				rightFlag[j] = 0;
			}
			cur = parents[tmpHeight + 1];
			tmpHeight++;
			i--;
		}
		/* printf("New Node Value: %d\n\n", cur->val); */
	}
	
	printf("Minimum Cost: %d\n", leastPathCost);
	return k;
}

int main()
{
	const char *filename = "input.txt";
	FILE *file;
	int num, len, i;
	clock_t timer;
	int pathArray[50];

	struct AVLTree *tree = newAVLTree(); /*return an empty tree */
	
	file = fopen(filename, "r");
	assert(file != 0);

	/* Read input file and add numbers to the AVL tree */
	while((fscanf(file, "%i", &num)) != EOF){
		addAVLTree(tree, num);		
	}

	timer = clock();

	/* Find the minimum-cost path in the AVL tree*/
	pathArray[0] = tree->root->val;
	len = FindMinPath(tree, pathArray);

	/* Print out all numbers on the minimum-cost path */
	printf("The minimum-cost path is: ");
	for(i = 0; i < len; i++)
		printf("%d ", pathArray[i]);
	printf("\n");

	fclose(file);
	timer = clock() - timer;
	printf("\nExecution time is %f seconds\n", (float)timer / (float)CLOCKS_PER_SEC);
	deleteAVLTree(tree); 

	return 0;
}



