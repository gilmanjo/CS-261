#include "listbag.h"
#include "type.h"
#include <assert.h>
#include <stdlib.h>

/*
	function to initialize the list, set the sentinels and set the size
	param lst the list
	pre: lst is not null
	post: lst size is 0
*/

void initList (struct list *lst) {
	assert(lst != NULL);

	/* Allocate space for sentinels */
	lst->head = (struct DLink*) malloc(sizeof(struct list));
	assert(lst->head != NULL);
	lst->tail = (struct DLink*) malloc(sizeof(struct list));
	assert(lst->tail != NULL);

	/* Set initial values for the list and sentinels */
	lst->size = 0;
	lst->head->value = 0;
	lst->tail->value = 0;
	lst->head->next = NULL;
	lst->head->prev = lst->tail;
	lst->tail->next = lst->head;
	lst->tail->prev = NULL;
}


/*
	_addLink
	Funtion to add a value v to the list before the link l
	param: lst the list
	param: lnk the  link to add before
	param: v the value to add
	pre: lst is not null
	pre: lnk is not null
	post: lst is not empty
*/

void _addLink(struct list *lst, struct DLink *lnk, TYPE v)
{
	/* Verify the pre-conditions */
	assert(lst != NULL);
	assert(lnk != NULL);

	/* Allocate new link */
	struct DLink *newLnk = (struct DLink*) malloc(sizeof(struct DLink));
	assert(newLnk != NULL);

	/* Insert new link inbetween link and link before link */
	newLnk->value = v;
	newLnk->next = lnk;
	newLnk->prev = lnk->prev;
	lnk->prev->next = newLnk;
	lnk->prev = newLnk;

	lst->size++;
}


/*
	addFrontList
	Function to add a value to the front of the list, can use _addLink()
	param: lst the list
	param: e the element to be added
	pre: lst is not null
	post: lst is not empty, increased size by 1
*/

void addFrontList(struct list *lst, TYPE e)
{
	/* Verify pre-condition */
	assert(lst != NULL);

	/* Insert link before the head sentinel and increase the size */
	_addLink(lst, lst->head, e);
}

/*
	addBackList
	Function to add a value to the back of the list, can use _addlink()
	param: lst the list
	pre: lst is not null
	post: lst is not empty
*/

void addBackList(struct list *lst, TYPE e) {
	/* Verify the pre-condition */
	assert(lst != NULL);

	/* Insert the link after the tail sentinel and increase the size */
	_addLink(lst, lst->tail->next, e);
}

/*
	frontList
	function to return the element in the front of the  list
	param: lst the list
	pre: lst is not null
	pre: lst is not empty
	post: none
*/

TYPE frontList (struct list *lst) {
	TYPE returnValue;
	returnValue = lst->head->prev->value;
	return returnValue;
}

/*
	backList
	function to return the element in the back of the  list
	param: lst the list
	pre: lst is not null
	pre: lst is not empty
	post: lst is not empty
*/

TYPE backList(struct list *lst)
{
	TYPE returnValue;

	lst->tail->next->value = returnValue;
	return returnValue;
}

/*
	_removeLink
	Function to remove a given link
	param: lst the list
	param: lnk the linke to be removed
	pre: lst is not null
	pre: lnk is not null
	post: lst size is reduced by 1
*/

void _removeLink(struct list *lst, struct DLink *lnk)
{
	/* Verify the pre-conditions */
	assert(lst != NULL);
	assert(lnk != NULL);

	/* Delete the link */
	free(lnk);
	lst->size--;
}

/*
	removeFrontList
	Function to remove element from front of list, can use _removelink()
	param: lst the list
	pre:lst is not null
	pre: lst is not empty
	post: size is reduced by 1
*/

void removeFrontList(struct list *lst) {
	/* Verify pre-conditions */
	assert(lst != NULL);
	assert(lst->size > 0);

	/* Create pointer to link to be deleted */
	struct DLink *delLnk = lst->head->prev;
	lst->head->prev->prev->next = lst->head;
	lst->head->prev = lst->head->prev->prev;
	_removeLink(lst, delLnk);
}

/*
	removeBackList
	Function to remove element from back of list, can use _removelink()
	param: lst the list
	pre: lst is not null
	pre:lst is not empty
	post: size reduced by 1
*/

void removeBackList(struct list *lst)
{
	/* Verify pre-conditions */
	assert(lst != NULL);
	assert(lst->size > 0);

	/* Create pointer to link to be deleted */
	struct DLink *delLnk = lst->tail->next;
	lst->tail->next->next->prev = lst->tail;
	lst->tail->next = lst->tail->next->next;
	_removeLink(lst, delLnk);
}

/*
	isEmptyList
	param: q the list
	pre: q is not null
	post: none
*/

int isEmptyList(struct list *lst) {
	/* Verify pre-condition */
	assert(lst != NULL);

	if(lst->size > 0)
		return 0;

	else
		return 1;
}



/* Recursive implementation of contains()
 Pre: current is not null
 Post: 1 if found, 0 otherwise
 */
int _contains_recursive(struct DLink* current, TYPE e){
	/* Verify pre-condition */
	assert(current != NULL);

	if(EQ(current->prev->prev, NULL)) 
		return 0;

	else if(EQ(current->value, e))
		return 1;

	else
		return _contains_recursive(current->prev, e);
}

/* Wrapper function for contains
 Pre: lst is not null
 Post: 1 if found, 0 otherwise
 */
int listContains (struct list *lst, TYPE e) {
	assert(!isEmptyList(lst));
	return _contains_recursive(lst->head, e);
}

/* Recursive implementation of remove()*/
void _remove_recursive(struct DLink* current, TYPE e, int* sz){
	if(EQ(current->value, e)) {
		current->next->prev = current->prev;
		current->prev->next = current->next;
		free(current);
		*sz--;
	}

	else if(!EQ(current->prev->prev, NULL)) {
		_remove_recursive(current->prev, e, sz);
	}
}
/* Wrapper for remove()*/
void listRemove (struct list *lst, TYPE e) {
	assert(!isEmptyList(lst));
	int *sz;
	sz = &(lst->size);
	_remove_recursive(lst->head, e, sz);
}


void freeList(struct list *q)
{
	/* Iterate through list, removing each link until the tail sentinel is
	reached */
	struct DLink *itrLnk = q->head->prev;
  while(itrLnk != q->tail) {
    removeFrontList(q);
    itrLnk = itrLnk->prev;
  }

  /* Free both sentinels and then the list itself */
  free(q->head);
  free(q->tail);
  free(q);
}



