/*
Austin Johnson
COEN 12
T 5:15-8:00
Crearting an unsorted array ADT
*/
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "set.h"


typedef struct set {
	char **data;
	int length;
	int count;
}SET;

static int search(char **, int, char *, int *);

/*Creates the new set
 *MaxElts is maximum size of the array
 *O(1) runtime
 */
SET *createSet(int maxElts){
	SET *sp = malloc(sizeof(SET));
	assert(sp!=NULL);
	sp->length = maxElts;
	sp->count = 0;
	sp->data = malloc(sizeof(char *)*maxElts);
	assert(sp->data != NULL);
	return sp;
}

/*Destroys the set sent to it in the parameter
 *sp is the set to be destroyed
 *O(n) runtime
 */
void destroySet(SET *sp){
	assert(sp!=NULL);
	int i;
	for (i = sp->length-1; i >= 0; i--){
		free(sp->data[i]);
	}
	free(sp->data);
	free(sp);
	return;	
}
/*Returns the number of elements
 *
 *O(1)
 */
int numElements(SET *sp){
	assert(sp!=NULL);
	SET set = *sp;
	return sp->count;
}

/*Adds element to the end of the array held in set sp
 *
 *O(n)
 */
void addElement(SET *sp, char *elt){
	assert(sp!=NULL);
	if (sp->count == sp->length){
		return;
	}
	int x = 0;
	int i = search(sp->data, sp->count, elt, &x);
	if (x==1)
		return;
	sp->data[sp->count]=strdup(elt);
	sp->count++;
	return;
}

/*Searches array for match with elt then it removes it from the set
 *
 *O(n)
 */
void removeElement(SET *sp, char *elt){
	assert(sp!=NULL);
	int x;
	int i = search(sp->data, sp->count, elt, &x);
	if (i == -1)
		return;
	free(sp->data[i]);
	sp->data[i] = sp->data[sp->count-1];
	sp->data[sp->count-1] = NULL;
	sp->count--;
	return;
}

/*Returns the pointer to the element identical to elt
 *
 *O(n)
 */
char *findElement(SET *sp, char *elt){
	assert(sp!=NULL);
	int x;
	int i = search(sp->data, sp->count, elt, &x);
	if (i != -1)
		return sp->data[i];
	else
		return NULL;
}

/*Returns an array of all the elements stored in sp->data
 *
 *O(n)
 */
char **getElements(SET *sp){
	assert(sp!=NULL);
	char **words = malloc(sizeof(char *)*sp->count);
	for (int i = 0; i < sp->count; i++){
		words[i] = sp->data[i];
	}
	return words;
}

/*returs the location of the element elt in the sp->data. If none returns -1
 *
 *O(n)
 */
static int search(char **data, int size, char *elt, int *found){
	int i;
	for (i = 0; i < size; i++){
		if (strcmp(data[i],elt)==0){
			*found = 1;
			return i;
		}
	}
	return -1;
}
