#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "set.h"
#include "list.h"

#define LISTCO 20;

typedef struct set {
	int count;
	int lcount;
	LIST **lists;
	int (*compare)();
	unsigned (*hash)();
}SET;

//creates the set and initializes lists
//O(n)
SET *createSet(int maxElts, int (*compare)(), unsigned (*hash)()){
	SET *sp = malloc(sizeof(SET));
	assert(sp!=NULL);
	sp->count = 0;
	sp->compare = compare;
	sp->hash = hash;
	sp->lcount = maxElts/LISTCO;
	sp->lists = malloc(sizeof(LIST *)*sp->lcount);
	int i;
	for (i = 0; i < sp->lcount; i++){
		sp->lists[i] = createList(sp->compare);
		assert(sp->lists[i] != NULL);
	}
	return sp;
}
//destroys all memory allocated
//O(n)
void destroySet(SET *sp){
	int i;
	for (i = 0; i < sp->lcount; i++){
		destroyList(sp->lists[i]);
	}
	free(sp->lists);
	free(sp);
	return;
}
//returns num of elements
//O(1)
int numElements(SET *sp){
	assert(sp!=NULL);
	return sp->count;
}
//hashes then adds the elt to the list
//O(n)
void addElement(SET *sp, void *elt){
	assert(elt != NULL && sp->compare != NULL);
	int loc = (*sp->hash)(elt)%sp->lcount;	
	if (findItem(sp->lists[loc],elt)!=NULL)
		return;
	addFirst(sp->lists[loc], elt);
	sp->count++;
	return;
}
//hashes then removes that elt from list
//O(n)
void removeElement(SET *sp, void *elt){
	assert(sp != NULL && elt != NULL);
	int loc = (*sp->hash)(elt)%sp->lcount;
	if (findItem(sp->lists[loc],elt)==NULL)
		return;
	removeItem(sp->lists[loc], elt);
	sp->count--;
	return;
}
//returns pointer of elt identical to elt
//O(n)
void *findElement(SET *sp, void *elt){
	assert(sp != NULL && elt != NULL);
	int loc = (*sp->hash)(elt)%sp->lcount;
	return findItem(sp->lists[loc],elt);
}
//returns the array of all elts in set
//O(n)
void *getElements(SET *sp){
	int i, j;
	void **elements = malloc(sizeof(void *)*sp->count);
	
	for (i = 0, j = 0; i < sp->lcount; i++){
		if (numItems(sp->lists[i])>0){
			memcpy(elements+j, getItems(sp->lists[i]), sizeof(void *)*numItems(sp->lists[i]));
			j += numItems(sp->lists[i]);
		}
	}
	return elements;	
}
