#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "cirListDeque.h"

/* internal functions interface */
struct DLink* _createLink (TYPE val);
void _addLinkAfter(struct cirListDeque *q, struct DLink *lnk, struct DLink *newLnk);
void _removeLink(struct cirListDeque *q, struct DLink *lnk);

/* ************************************************************************
	Deque Functions
************************************************************************ */

/* Initialize deque.

	param: 	q		pointer to the deque
	pre:	q is not null
	post:	q->Sentinel is allocated and q->size equals zero
*/
void initCirListDeque (struct cirListDeque *q) 
{
	assert(q != NULL);
	q->Sentinel = (struct DLink*) malloc(sizeof(struct DLink));
	assert(q->Sentinel != NULL);
	
	q->size = 0;
	q->Sentinel->value = 0;
	q->Sentinel->next = q->Sentinel;
	q->Sentinel->prev = q->Sentinel;
}

/* Create a link for a value.

	param: 	val		the value to create a link for
	pre:	none
	post:	a link to store the value
*/
struct DLink * _createLink (TYPE val)
{
	struct DLink *newLink = (struct DLink*) malloc(sizeof(struct DLink));
	assert(newLink != NULL);

	newLink->value = val;
	return newLink;
}

/* Adds a link after another link

	param: 	q		pointer to the deque
	param: 	lnk		pointer to the existing link in the deque
	param: 	newLnk	pointer to the new link to add after the existing link
	pre:	q is not null
	pre: 	lnk and newLnk are not null
	pre:	lnk is in the deque 
	post:	the new link is added into the deque after the existing link
*/
void _addLinkAfter(struct cirListDeque *q, struct DLink *lnk, struct DLink *newLnk)
{
	assert(q != NULL);
	assert(lnk != NULL && newLnk != NULL);
	/* Point the existing link's next pointer to the new link and point the new
	link's prev pointer to the existing link */
	lnk->next = newLnk;
	newLnk->prev = lnk;

	/* Increase the size of the Linked List*/
	q->size++;
}

/* Adds a link to the back of the deque

	param: 	q		pointer to the deque
	param: 	val		value for the link to be added
	pre:	q is not null
	post:	a link storing val is added to the back of the deque
*/
void addBackCirListDeque (struct cirListDeque *q, TYPE val) 
{
	/* Verify pre-conditions */
	assert(q != NULL);

	struct DLink *newLink = _createLink(val);
	_addLinkAfter(q, q->Sentinel->prev, newLink);
	newLink->next = q->Sentinel;
	q->Sentinel->prev = newLink;
}

/* Adds a link to the front of the deque

	param: 	q		pointer to the deque
	param: 	val		value for the link to be added
	pre:	q is not null
	post:	a link storing val is added to the front of the deque
*/
void addFrontCirListDeque(struct cirListDeque *q, TYPE val)
{
	/* Verify pre-condition */
	assert(q != NULL);

	struct DLink *newLink = _createLink(val);
	q->Sentinel->next->prev = newLink;
	newLink->next = q->Sentinel->next;
	_addLinkAfter(q, q->Sentinel, newLink);
}

/* Get the value of the front of the deque

	param: 	q		pointer to the deque
	pre:	q is not null and q is not empty
	post:	none
	ret: 	value of the front of the deque
*/
TYPE frontCirListDeque(struct cirListDeque *q) 
{
	/* Verify the pre-conditions */
	assert(q != NULL);
	assert(q->size > 0);

	TYPE val;
	val = q->Sentinel->next->value;
	return val;
}

/* Get the value of the back of the deque

	param: 	q		pointer to the deque
	pre:	q is not null and q is not empty
	post:	none
	ret: 	value of the back of the deque
*/
TYPE backCirListDeque(struct cirListDeque *q)
{
	/* Verify the pre-conditions */
	assert(q != NULL);
	assert(q->size > 0);

	TYPE val;
	val = q->Sentinel->prev->value;
	return val;
}

/* Remove a link from the deque

	param: 	q		pointer to the deque
	param: 	lnk		pointer to the link to be removed
	pre:	q is not null and q is not empty
	pre:	lnk is in the deque 
	post:	the link is removed from the deque
*/
void _removeLink(struct cirListDeque *q, struct DLink *lnk)
{
	free(lnk);
	q->size--;
}

/* Remove the front of the deque

	param: 	q		pointer to the deque
	pre:	q is not null and q is not empty
	post:	the front is removed from the deque
*/
void removeFrontCirListDeque (struct cirListDeque *q) {
	/* Verify the pre-conditions */
	assert(q != NULL);
	assert(q->size > 0);

	/* Create pointer to link to be deleted and then re-assign Sentinel's next
	and the second link's prev */
	struct DLink *delLink = q->Sentinel->next;
	assert(delLink != NULL);

	q->Sentinel->next = q->Sentinel->next->next;
	q->Sentinel->next->prev = q->Sentinel;
	_removeLink(q, delLink);
}


/* Remove the back of the deque

	param: 	q		pointer to the deque
	pre:	q is not null and q is not empty
	post:	the back is removed from the deque
*/
void removeBackCirListDeque(struct cirListDeque *q)
{
	/* Verify the pre-conditions */
	assert(q != NULL);
	assert(q->size != 0);

	/* Create pointer to link to be deleted and then re-assign Sentinel's next
	and the second link's prev */
	struct DLink *delLink = q->Sentinel->prev;
	assert(delLink != NULL);
	
	q->Sentinel->prev = q->Sentinel->prev->prev;
	q->Sentinel->prev->next = q->Sentinel;
	_removeLink(q, delLink);
}

/* De-allocate all links of the deque

	param: 	q		pointer to the deque
	pre:	none
	post:	All links (including backSentinel) are de-allocated
*/
void freeCirListDeque(struct cirListDeque *q)
{
	/* Remove links in the deque until only the Sentinel remains */
	while(q->size != 0) {
		removeBackCirListDeque(q);
	}

	/* Remove the Sentinel */
	_removeLink(q, q->Sentinel);
}

/* Check whether the deque is empty

	param: 	q		pointer to the deque
	pre:	q is not null
	ret: 	1 if the deque is empty. Otherwise, 0.
*/
int isEmptyCirListDeque(struct cirListDeque *q) {
	/* Verify pre-condition */
	assert(q != NULL);

	if(q->size > 0)
		return 0;

	else
		return 1;
}

/* Print the links in the deque from front to back

	param: 	q		pointer to the deque
	pre:	q is not null and q is not empty
	post: 	the links in the deque are printed from front to back
*/
void printCirListDeque(struct cirListDeque *q)
{
	/* Verify the pre-conditions */
	assert(q != NULL);
	assert(q->size > 0);

	/* Set iterator link to the first link in the deque and move it forward after
	printing each value */
	struct DLink *itrLink = q->Sentinel->next;
	assert(itrLink != NULL);

	while(itrLink != q->Sentinel) {
		printf("%g\n", itrLink->value);
		itrLink = itrLink->next;
	}
}

/* Reverse the deque

	param: 	q		pointer to the deque
	pre:	q is not null and q is not empty
	post: 	the deque is reversed
*/
void reverseCirListDeque(struct cirListDeque *q)
{
	/* Verify the pre-conditions */
	assert(q != NULL);
	assert(q->size > 0);

	/* Reverse the Sentinel */
	struct DLink *itrLinkA = q->Sentinel;
	struct DLink *itrLinkB;

	 do {
	 	itrLinkB = itrLinkA->next;
		itrLinkA->next = itrLinkA->prev;
		itrLinkA->prev = itrLinkB;
		itrLinkA = itrLinkA->next;
	} while(itrLinkA != q->Sentinel);
}
