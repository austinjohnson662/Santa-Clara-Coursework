/*
Austin Johnson
COEN 12 Lab 
T 5:15-8:00
Creating a sorted array ADT
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

/*creates a new set with an array of size maxElts
 *
 *O(1)
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

/*Destroys the set pointed to by sp
 *
 *O(n)
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

/*Returns the number of elements stored in the set
 *
 *O(1)
 */
int numElements(SET *sp){
	assert(sp!=NULL);
	return sp->count;
}

/*Adds the element in its alphabetical spot in the array
 *
 *O(n)
 */
void addElement(SET *sp, char *elt){
	assert(sp!=NULL);
	if (sp->count == sp->length){
		return;
	}
	int check = 0;
	int i, x = search(sp->data, sp->count-1, elt, &check);
	if (check == 1)
		return;
	for (i = sp->count; i >= x; i--){
		sp->data[i+1]=sp->data[i];
	}
	sp->data[x]=strdup(elt);
	sp->count++;
	return;
}

/*Removes item in set sp identical to elt
 *
 *O(n)
 */
void removeElement(SET *sp, char *elt){
	assert(sp!=NULL);
	int found = 0;
	int i, x = search(sp->data, sp->count, elt, &found);
	if (found == 0)
		return;
	free(sp->data[x]);
	for (i = x; i<sp->count-1; i++){
		sp->data[i] = sp->data[i+1];
	}
	sp->data[sp->count-1] = NULL;
	sp->count--;
	return;
}

/*returns the pointer to the element idetical to elt in set sp
 *
 *O(logn)
 */
char *findElement(SET *sp, char *elt){
	assert(sp!=NULL);
	int found = 0;
	int i = search(sp->data, sp->count-1, elt, &found);
	if (found == 1){
		return sp->data[i];
	}
	return NULL;
}

/*Returns an array of all the elemets stored in the set sp
 *
 *O(n)
 */
char **getElements(SET *sp){
	assert(sp!=NULL);
	char **words = malloc(sizeof(char *)*sp->count);
	int i;
	for (i = 0; i < sp->count; i++){
		words[i] = sp->data[i];
	}
	return words;
}

/*returs the location of the element elt in the sp->data. If none returns -u
 *
 *O(logn)
 */
static int search(char **data, int size, char *elt, int *found){
	int hi = size, lo = 0, mid;
	while (hi >= lo){
		mid = (hi + lo)/2;
		if (strcmp(elt, data[mid]) > 0){
			lo = mid + 1;
		} else if (strcmp(elt, data[mid]) < 0){
			hi = mid-1;
		} else {
			*found = 1;
			return mid;
		}
	}
	return lo;
}
