#include <assert.h>
#include <stdlib.h>
#include "hashMap.h"
#include "structs.h"
#include <string.h>

int stringHash1(char * str)
{
	int i;
	int r = 0;
	for (i = 0; str[i] != '\0'; i++)
		r += str[i];
	return r;
}

int stringHash2(char * str)
{
	int i;
	int r = 0;
	for (i = 0; str[i] != '\0'; i++)
		r += (i+1) * str[i]; /*the difference between 1 and 2 is on this line*/
	return r;
}

void initMap (struct hashMap * ht, int tableSize)
{
	int index;
	if(ht == NULL)
		return;
	ht->table = (hashLink**)malloc(sizeof(hashLink*) * tableSize);
	ht->tableSize = tableSize;
	ht->count = 0;
	for(index = 0; index < tableSize; index++)
		ht->table[index] = NULL;
}

void freeMap (struct hashMap * ht) {
	struct hashLink *nxt, *cur;

	int i;
	for(i = 0; i < ht->tableSize; i++) {
		cur = ht->table[i];
		while(cur != NULL) {
			nxt = cur->next;
			free(cur);
			cur = nxt;
		}
		ht->table[i] = 0;
	}
	free(ht->table);
	ht->tableSize = 0;
	ht->count = 0;
}

void insertMap (struct hashMap * ht, KeyType k, ValueType v) {
	int idx;

	struct hashLink *tmp = malloc(sizeof(struct hashLink));
	assert(tmp != NULL);

	tmp->next = 0;
	tmp->key = k;
	tmp->value = v;

	if(containsKey(ht, k)) {
		removeKey(ht, k);
	}

	idx = stringHash1(k) % ht->tableSize;

	if(idx < 0){
		idx += ht->tableSize;
	}

	if(!ht->table[idx]) {
		ht->table[idx] = tmp;
	}

	else {
		struct hashLink *cur = ht->table[idx];
		while(cur->next != NULL) {
			cur = cur->next;
		}
		cur->next = tmp;
	}
	ht->count++;
}

ValueType* atMap (struct hashMap * ht, KeyType k) {
	struct hashLink *cur;
	int idx = stringHash1(k) % ht->tableSize;
	if(idx < 0) {
		idx += ht->tableSize;
	}

	assert(containsKey(ht, k));
	cur = ht->table[idx];

	while(strcmp(cur->key, k) != 0) {
		cur = cur->next;
	}

	return &cur->value;
}

int containsKey (struct hashMap * ht, KeyType k) {
	struct hashLink *cur;
	int idx = stringHash1(k) % ht->tableSize;

	if(idx < 0)
		idx += ht->tableSize;

	cur = ht->table[idx];

	while(cur) {
		if(strcmp(cur->key, k) == 0)
			return 1;
		cur = cur->next;
	}
	return 0;
}

void removeKey (struct hashMap * ht, KeyType k) {
	struct hashLink *cur, *tmp = NULL;

	int idx = stringHash1(k) % ht->tableSize;
	if(idx < 0)
		idx += ht->tableSize;

	cur = ht->table[idx];
	while(strcmp(cur->key, k) != 0) {
		tmp = cur;
		cur = cur->next;
	}

	if(tmp)
		tmp->next = cur->next;
	else
		ht->table[idx] = 0;

	free(cur);
}

int sizeMap (struct hashMap *ht) {
	assert(ht != NULL);
	return ht->tableSize;
}

int capacityMap(struct hashMap *ht) {
	assert(ht != NULL);
	return ht->tableSize;
}

int emptyBuckets(struct hashMap *ht) {
	int count = 0;
	int i;
	for(i = 0; i < ht->tableSize; i++) {
		if(!ht->table[i])
			count++;
	}
	return count;
}

float tableLoad(struct hashMap *ht) {
	assert(ht != NULL);
	return ht->count / (double) ht->tableSize;
}
