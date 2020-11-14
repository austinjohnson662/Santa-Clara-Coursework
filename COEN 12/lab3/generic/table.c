#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "set.h"


typedef struct set {
	int count;
	int length;
	void** data;
	char* flags;
	int (*compare)();
	unsigned (*hash)();
}SET;

/*Searches for an element. If found the location is returned and found is set to 1. Otherwise, returns -1 and found is set to 0.
 *
 * O(n)(big O is dependent on the runtime of *sp->compare and *sp->hash)
 */
static int search(SET *sp, void *target, int *found){
	assert(sp!=NULL);
	int i = (*sp->hash)(target)%sp->length;
	int start = i;
	while (sp->flags[i] != 'E'){
		if (sp->flags[i]=='F'){
			if ((*sp->compare)(target, sp->data[i])==0){
				*found = 1;
				return i;
			}
		}
		i++;
		i = i % sp->length;
		if (i == start){
			*found = 0;
			break;
		}
	}
	*found = 0;
	return -1;
}

/*Creates a set. Compare and hash function are set as paramenters
 *
 *O(n)
 */
SET *createSet(int maxElts, int (*compare)(), unsigned (*hash)()){
	SET *sp = malloc(sizeof(SET));
	assert(sp!=NULL);
	sp->count = 0;
	sp->length = maxElts;
	sp->data = malloc(sizeof(void *)*maxElts);
	assert(sp->data!=NULL);
	sp->flags = malloc(sizeof(char)*maxElts);
	assert(sp->flags != NULL);
	sp->compare = compare;
	sp->hash = hash;
	int i;
	for (i = 0; i < sp->length; i++){
		sp->flags[i] = 'E';
	}
	return sp;
}

/*Frees all data allocated by the ADT
 *
 *O(1)
 */
void destroySet(SET *sp){
	assert(sp!=NULL);
	int i;
	free(sp->data);
	free(sp->flags);
	free(sp);
	return;
}

/*Returns the number of elements in the set given
 *
 *O(1)
 */
int numElements(SET *sp){
	assert(sp != NULL);
	return sp->count;
}

/*Adds an elements to the hashed location, and if it cannot it will prob until an empty spot can be found.
 *
 *O(n)
 */
void addElement(SET *sp, void *elt){
	assert(sp!=NULL);
	int found = 0;
	int x = search(sp, elt, &found);
	if ((sp->count == sp->length)||found==1)
		return;
	int i = sp->hash(elt)%sp->length;
	while (sp->flags[i] == 'F'){
		i++;
		i = i%sp->length;
	}
	sp->flags[i] = 'F';
	sp->data[i] = elt;
	sp->count++;
	return;	
}

/*Removes an element identical to the value of elt
 *
 *O(n)
 */
void removeElement(SET *sp, void *elt){
	assert(sp!=NULL);
	int found = 0;
	int x = search(sp, elt,&found);
	if (found == 0)
		return;
	sp->flags[x] = 'D';
	sp->data[x] = NULL;
	sp->count--;
	return;
}

/*Finds element identical to elt
 *
 *O(n)
 */
void *findElement(SET *sp, void *elt){
	assert(sp!=NULL);
	int x;
	int loc = search(sp, elt, &x);
	if (x == 0)
		return NULL;
	return sp->data[loc];
}

/*Returns an array of the elements passed to it.
 *
 *O(n)
 */
void *getElements(SET *sp){
	assert(sp!=NULL);
	void **elts = malloc(sizeof(void *)*sp->length);
	int i;
	int count = 0;
	for (i = 0; i < sp->length; i++){
		if (sp->flags[i]=='F'){
			elts[count]=sp->data[i];
			count++;
		}
	}
	return elts;
}






