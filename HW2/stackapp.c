/*	stackapp.c: Stack application. */
#include <stdio.h>
#include <stdlib.h>
#include "dynArray.h"


/* ***************************************************************
Using stack to check for unbalanced parentheses.
***************************************************************** */

/* Returns the next character of the string, once reaches end return '0' (zero)
	param: 	s pointer to a string 	
	pre: s is not null		
*/
char nextChar(char* s)
{
	static int i = -1;	
	char c;
	++i;	
	c = *(s+i);			
	if ( c == '\0' )
		return 0;	
	else 
		return c;
}

/* Checks whether the (), {}, and [] are balanced or not
	param: 	s pointer to a string 	
	pre: s is not null	
	post:	
*/
int isBalanced(char* s)
{
	/* Verify pre-condition */
	/* assert(s != NULL); */

	/* Initialize stack parameters */
	int balanced = 0;
	DynArr *paraStack = newDynArr(2);

	/* Iterated through string until null character is found */
	int i = 0;
	while(!EQ(nextChar(s), 0)) {

		/*
		Switch statement runs code for any parentheses character found.
		If a beginning parenthese is found, it's ending equivalent is pushed
		to the stack.  If an ending is found, it is checked against the top
		of the stack for equality.  If they are equal, the stack is popped.

		In the case where an ending parenthese may be found while the stack is
		empty, an error flag, denoted 'e' is pushed onto the stack.  This is
		used to immediately identify an unbalanced expression
		*/
		
		switch(s[i]) {
			case '(':
				pushDynArr(paraStack, ')');
				break;
			case '{':
				pushDynArr(paraStack, '}');
				break;
			case '[':
				pushDynArr(paraStack, ']');
				break;
			case ')':
				if(EQ(isEmptyDynArr(paraStack), 1)) {
					pushDynArr(paraStack, 'e');
				}
				else if(EQ(')', topDynArr(paraStack))) {
					popDynArr(paraStack);
				}
				break;
			case '}':
				if(EQ(isEmptyDynArr(paraStack), 1)) {
					pushDynArr(paraStack, 'e');
				}
				else if(EQ('}', topDynArr(paraStack))) {
					popDynArr(paraStack);
				}
				break;
			case ']':
				if(EQ(isEmptyDynArr(paraStack), 1)) {
					pushDynArr(paraStack, 'e');
				}
				else if(EQ(']', topDynArr(paraStack))) {
					popDynArr(paraStack);
				}
				break;
		}

		i++;
	}

	/* Verify that no parentheses remain on the stack */
	if(EQ(isEmptyDynArr(paraStack), 1))
		balanced = 1;

	/* Free memory and return balanced status (0 = unbalanced, 1 = balanced) */
	deleteDynArr(paraStack);
	return balanced;
}

int main(int argc, char* argv[]){

	printf("Assignment 2\n");
	
	char* s=argv[1];	
	int res;
	
	res = isBalanced(s);

	if (res)
		printf("The string %s is balanced\n",s);
	else 
		printf("The string %s is not balanced\n",s);
	
	return 0;	
}
