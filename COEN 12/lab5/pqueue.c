#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "pqueue.h"


#define STARTERL 10

typedef struct pqueue {
	int (*compare)();
	int length;//size of array
	int count;//# of items
	void **data;//where data is held (in an array)
}PQ;

//Creates a priority queue
//
//O(1)
PQ *createQueue(int (*compare)()){
	PQ *pq = malloc(sizeof(PQ));
	assert(pq != NULL);
	pq->data = malloc(sizeof(void *)*STARTERL);
	assert(pq->data != NULL);
	pq->length = STARTERL;
	pq->count = 0;
	pq->compare = compare;
	return pq;
}
//Frees all memory allocaqted
//
//O(1)
void destroyQueue(PQ *pq){
	assert(pq != NULL);
	int i;
	for (i = 0; i < pq->count;i++){
		free(pq->data[i]);
	}
	free(pq->data);
	free(pq);
	return;
}

//Returns number of elements in priority queue
//
//O(1)
int numEntries(PQ *pq){
	assert(pq!=NULL);
	return pq->count;
}

//Adds an element to the priority queue
//
//O(logn)
void addEntry(PQ *pq, void *entry){
	assert(pq!=NULL && entry!=NULL);
	if (pq->count == pq->length){
		pq->data = realloc(pq->data, sizeof(void *)*pq->length*2);
		pq->length *= 2;
	}
	pq->data[pq->count] = entry;
	pq->count++;
	void *temp;
	int loc = pq->count-1; //keeps track of the item
	int pNext = (loc-1)/2;
	while ((*pq->compare)(pq->data[loc],pq->data[pNext])<0){
		temp = pq->data[loc];
		pq->data[loc] = pq->data[pNext];
		pq->data[pNext] = temp;
		loc = pNext;
		pNext = (pNext-1)/2;
	}
	return;
}
//Removes the smallest entry from the data set
//
//O(logn)
void *removeEntry(PQ *pq){
	assert(pq!=NULL);
	void *rValue = pq->data[0], *temp;
	if (pq->count == 0)
		return NULL;

	pq->data[0] = pq->data[pq->count-1];
	pq->count--;
	int loc = 0, pNextL = 1, pNextR = 2, min;
	
	while (pNextL < pq->count){
		if (pNextR < pq->count){
			if ((*pq->compare)(pq->data[pNextL],pq->data[pNextR])>=0){
				min = pNextR;
			} else {
				min = pNextL;
			}
		} else {
			min = pNextL;
		}
		if ((*pq->compare)(pq->data[loc], pq->data[min])<=0)
			break;
		temp = pq->data[loc];
		pq->data[loc] = pq->data[min];
		pq->data[min] = temp;
		loc = min;
		pNextL = (loc*2)+1;
		pNextR = (loc*2)+2;
	}

	return rValue;
}














