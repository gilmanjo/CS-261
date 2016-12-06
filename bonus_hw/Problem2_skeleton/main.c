#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "hashMap.h"

/*
 the getWord function takes a FILE pointer and returns you a string which was
 the next word in the in the file. words are defined (by this function) to be
 characters or numbers seperated by periods, spaces, or newlines.
 
 when there are no more words in the input file this function will return NULL.
 
 this function will malloc some memory for the char* it returns. it is your job
 to free this memory when you no longer need it.
 */
char* getWord(FILE *file); /* prototype */

/****************************************/

int main (int argc, const char * argv[]) {

	int i;
	FILE *inputFile;
	struct hashLink *current;
	const char *filename;

	struct hashMap hashTable;
	int tableSize = 100;

	if(argc == 2)
		filename = argv[1];
	else
		filename = "input.txt";

	initMap(&hashTable, tableSize);
	inputFile = fopen(filename, "r");
	while(!feof(inputFile)) {
		char *word = getWord(inputFile);
		if(word != NULL) {
			if(containsKey(&hashTable, word)) {
				int *value = atMap(&hashTable, word);
				++(*value);
			}

			else
				insertMap(&hashTable, word, 1);
		}
	}

	for(i = 0; i < hashTable.tableSize; i++) {
		current = hashTable.table[i];
		while(current != NULL) {
			current = current->next;
		}
	}

	freeMap(&hashTable);
	fclose(inputFile);
	return 0;
}

char *getWord(FILE *file) {
	int length = 0;
	int capacity = 16;
	char letter;

	char *word = (char *) malloc(sizeof(char) * capacity);
	assert(word != NULL);

	while((letter = fgetc(file)) != EOF) {
		if((length + 1) > capacity) {
			capacity *= 2;
			word = (char *)realloc(word, capacity);
		}

		if((letter >= '0' && letter <= '9') ||
			(letter >= 'A' && letter <= 'Z') ||
			(letter >= 'a' && letter <= 'z') ||
			letter == 39) {
			word[length] = letter;
		length++;
		}

		else if(length > 0)
			break;
	}

	if(length == 0) {
		free(word);
		return NULL;
	}

	word[length] = '\0';
	return word;
}