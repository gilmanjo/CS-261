#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "skipList.h"
#include <time.h>	


/* ************************************************************************
Main Function
 ************************************************************************ */
/* Test function:
 param: no parameters
 pre:	no parameres
 post: prints out the contents of the skip list */

void test(){
	int i;
	
	/*  FIX ME */
	
	/*  Initialize the skip list */
	struct skipList * slst = (struct skipList *) malloc(sizeof(struct skipList));
	initSkipList(slst);



	/*  Add to the skip list  M = 20 random integers in [0,100] */
		for(i = 0; i < 20; i++) 
		addSkipList(slst, (rand() % 101)); 

	
	/*  Print out the contents of the skip list in the breadth-first order, starting from top. 
	 While printing the elements, move to a new line every time you reach the end of one level, 
	 and move down to the lower level of the skip list. 
	 For example, the print out of a skip list with 5 elements should look like
	 
	 7
	 7 14 29
	 3 7 9 14 20
	 
	 */
	 printSkipList(slst);
	 
	/* Develop test cases for evaluating the following functions:  
	 int containsSkipList(struct skipList *slst, TYPE e) 
	 int removeSkipList(struct skipList *slst, TYPE e)
	 */
	 printf("%d\n", containsSkipList(slst, 7));
	 printf("%d\n", containsSkipList(slst, 20));
	 removeSkipList(slst, 7);
	 printSkipList(slst);
	 removeSkipList(slst, 15);
	 printSkipList(slst);
	 printf("%d\n", containsSkipList(slst, 7));
	 printf("%d\n", containsSkipList(slst, 20));
}


/* ************************************************************************
Internal Functions
 ************************************************************************ */

/* Coin toss function:
 param: 	no parameters
 pre:	no parameres
 post: output is a random intiger number in {0,1} */
int flipSkipLink(void)
{
	return (rand() % 2);
}

/* Move to the right as long as the next element is smaller than the input value:
 param: 	current -- pointer to a place in the list from where we need to slide to the right
 param:	e --  input value
 pre:	current is not NULL
 post: returns one link before the link that contains the input value e */
struct skipLink * slideRightSkipList(struct skipLink *current, TYPE e){
	assert(current != NULL);

	while ((current->next != 0) && LT(current->next->value, e))
		current = current->next;
	
	return current;
}


/* Create a new skip link for a value
	param: e	 -- the value to create a link for
	param: nextLnk	 -- the new link's next should point to nextLnk
	param: downLnk -- the new link's down should point to downLnk
	pre:	none
	post:	a link to store the value */
struct skipLink* newSkipLink(TYPE e, struct skipLink * nextLnk, struct skipLink* downLnk) {
	struct skipLink * tmp = (struct skipLink *) malloc(sizeof(struct skipLink));
	assert(tmp != 0);
	tmp->value = e;
	tmp->next = nextLnk;
	tmp->down = downLnk;
	return tmp;
}


/* Add a new skip link recursively
 param: current -- pointer to a place in the list where the new element should be inserted
 param: e	 -- the value to create a link for
 pre:	current is not NULL
 post: a link to store the value */
struct skipLink* skipLinkAdd(struct skipLink * current, TYPE e) {
	struct skipLink *newLink, *downLink;
	newLink = 0;
	if (current->down == 0) {
		newLink = newSkipLink(e, current->next, 0);
		current->next = newLink;
	}
	else {
		downLink = skipLinkAdd(slideRightSkipList(current->down, e), e);
		if (downLink != 0 && flipSkipLink()) {
			newLink = newSkipLink(e, current->next, downLink);
			current->next = newLink;
		}
	}
	return newLink;
}


/* ************************************************************************
Public Functions
 ************************************************************************ */

/* Initialize skip list:
 param:  slst -- pointer to the skip list
 pre:	slst is not null
 post: the sentinels are allocated, the pointers are set, and the list size equals zero */
void initSkipList (struct skipList *slst) 
{
	/* Assert pre-conditions and set RNG seed */
	srand((unsigned) time(NULL));
	assert(slst != NULL);

	/* Create sentinel skiplink */
	struct skipLink * sent = (struct skipLink *) malloc(sizeof(struct skipLink));
	assert(sent != NULL);

	/* Initialize member variables and set topSentinel to new skipLink */
	sent->next = 0;
	sent->down = 0;
	sent->value = 0;
	slst->topSentinel = sent;
}

/* Checks if an element is in the skip list:
 param: slst -- pointer to the skip list
 param: e -- element to be checked
 pre:	slst is not null
 post: returns true or false  */
int containsSkipList(struct skipList *slst, TYPE e)
{
	/* Assert pre-condition */
	assert(slst != NULL);

	/* Create skip link pointer for searching and start at top Sentinel */
	struct skipLink *searchLink;
	searchLink = slst->topSentinel;

	/* Iterate through skip list until value is found or reach end of list */
	do {
		searchLink = slideRightSkipList(searchLink, e);

		/* Check if the next link contains the value */
		if((searchLink->next != NULL) && (EQ(searchLink->next->value, e)))
			return 1;

		/* Move down a level */
		searchLink = searchLink->down;
	} while((searchLink != 0));
		return 0;
}


/* Remove an element from the skip list:
 param: slst -- pointer to the skip list
 param: e -- element to be removed
 pre:	slst is not null
 post: the new element is removed from all internal sorted lists */
void removeSkipList(struct skipList *slst, TYPE e)
{
	/* Assert pre-condition */
	assert(slst != NULL);

	/* Create pointer to skip link for searching and a temp link
	for deleting links */
	struct skipLink *searchLink, *tempLink;
	searchLink = slst->topSentinel;

	/* Iterate through levels, deleting links with value e, until the
	bottom level is reached */
	do{
		searchLink = slideRightSkipList(searchLink, e);

		if(!EQ(searchLink->next, NULL) && EQ(searchLink->next->value, e)) {
			tempLink = searchLink->next;
			searchLink->next = searchLink->next->next;
			free(tempLink);

			/* Decrement size of skip list if match is found on bottom level */
			if(!EQ(searchLink->down, 0))
				slst->size--;
		}

		/* Move down a level */
		searchLink = searchLink->down;
	} while(!EQ(searchLink, NULL));

	/* If the top row is empty in a multi-row skip list, delete it */
	if(EQ(slst->topSentinel->next, NULL) && !EQ(slst->topSentinel->down, 0)) {
		tempLink = slst->topSentinel;
		slst->topSentinel = slst->topSentinel->down;
		free(tempLink);
	}
}


/* Add a new element to the skip list:
	param: slst -- pointer to the skip list
	param: e -- element to be added
	pre:	slst is not null
	post:	the new element is added to the lowest list and randomly to higher-level lists */
void addSkipList(struct skipList *slst, TYPE e)
{
	/* Assert pre-condition */
	assert(slst != NULL);

	/* Add new skip link to the skip list */
	struct skipLink *downLink, *newLink;
	downLink = skipLinkAdd(slideRightSkipList(slst->topSentinel,e),e);

	/* Flip a coin on creating a new top list */
	if (downLink != 0 && flipSkipLink()) {
		newLink = newSkipLink(e, 0, downLink);
		slst->topSentinel = newSkipLink(0, newLink, slst->topSentinel);
	}
	
	/* Increment size of the skip list */
	slst->size++;

}


/* Find the number of elements in the skip list:
 param: slst -- pointer to the skip list
 pre:	slst is not null
 post: the number of elements */
int sizeSkipList(struct skipList *slst)
{
	assert(slst != NULL);
	return slst->size;	
}

/* Print the links in the skip list:
	param: slst -- pointer to the skip list
	pre:	slst is not null and slst is not empty
	post: the links in the skip list are printed breadth-first, top-down */
void printSkipList(struct skipList *slst)
{
	/* Assert pre-conditions */
	assert(slst != NULL);
	assert(slst->size != 0);

	/* Skip link pointers to iterate through skip list */
	struct skipLink *printLink, *headLink;
	printLink = slst->topSentinel;
	printf("\n");

	/* Print each row */
	do {
		headLink = printLink->down;

		/* Print each link in a row */
		while(printLink->next != NULL) {
			printf("%g ", printLink->next->value);
			printLink = printLink->next;
		}
		printf("\n");
		printLink = headLink;
	} while(printLink != 0);
}

/* Merge two skip lists, by adding elements of skip list 2 to skip list 1 
   that are not already contained in skip list 1. 
   The function is also supposed to remove the entire skip list 2 from the memory.
   param: slst1 -- pointer to the skip list 1
   param: slst2 -- pointer to the skip list 2
   pre: slst1 and slst2 are not null, and skip list 1 and skip list 2 are not empty
   post: slst1 points to the merger skip list,  slst2 is null*/
void mergeSkipList(struct skipList *slst1, struct skipList *slst2)
{

	/* Assert pre-conditions */
	assert(slst1 != NULL && slst2 != NULL);
	assert(slst1->size != 0 && slst2->size != 0);

	struct skipLink *searchLink, *deleteLink;

	/* Iterate to bottom of skip list 2 */
	deleteLink = slst2->topSentinel;
	while(deleteLink->down != 0)
		deleteLink = deleteLink->down;

	/* Check if each value in skip list 2 is in skip list 1 */
	searchLink = deleteLink;
	while(searchLink->next != NULL) {

		/* Add a value from skip list 2, if it is not in skip list 1 */
		if(!containsSkipList(slst1, searchLink->value))
			addSkipList(slst1, searchLink->value);
		
		searchLink = searchLink->next;
	}

	/* Delete all skip links in skip list 2 */
	while(deleteLink->next != NULL) {
		removeSkipList(slst2, deleteLink->next->value);
	
	}

	/* Delete sentinel links */
	while(slst2->topSentinel->down != 0) {
		deleteLink = slst2->topSentinel;
		slst2->topSentinel = slst2->topSentinel->down;
		free(deleteLink);
	}
	free(slst2->topSentinel);

	/* Free skip list 2 */
	free(slst2);
	assert(slst2 != NULL);
	slst2 = NULL;
	
}
