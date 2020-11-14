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
}SET;

/*Function given to hash a string.
 *
 *O(n)
 */
unsigned strhash(char *s){
	unsigned hash = 0;
	while (*s != '\0'){
		hash = 31 * hash + *s++;
	}
	return hash;
}

/*Searches a function for a target. If target is present return the location, otherwise returns the location where thee last location it would be. Sets found to 1 if the target is found and sets it to 0 if not.
 *
 *O(n)
 */
static int search(SET *sp, char *target, int *found){
	assert(sp!=NULL);
	int i = strhash(target)%sp->length;
	int start = i;
	while (sp->flags[i] != 'E'){
		if (sp->flags[i]=='F'){
			if (strcmp(target, sp->data[i])==0){
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
	return i;
}

/*Creates the set and allocates the memory for the set
 *
 *O(n)
 */
SET *createSet(int maxElts){
	SET *sp = malloc(sizeof(SET));
	assert(sp!=NULL);
	sp->count = 0;
	sp->length = maxElts;
	sp->data = malloc(sizeof(char *)*maxElts);
	assert(sp->data!=NULL);
	sp->flags = malloc(sizeof(char)*maxElts);
	assert(sp->flags != NULL);
	int i;
	for (i = 0; i < sp->length; i++){
		sp->flags[i] = 'E';
	}
	return sp;
}

/*Destroys the data allocated by the ADT.
 *
 *O(n)
 */
void destroySet(SET *sp){
	assert(sp!=NULL);
	int i;
	for (i = sp->length-1; i >= 0; i--)
		free(sp->data[i]);
	free(sp->data);
	free(sp->flags);
	free(sp);
	return;
}

/*Returns the size of the set given.
 *
 *O(1)
 */
int numElements(SET *sp){
	assert(sp != NULL);
	return sp->count;
}

/*Adds the element to the hashed location and if not uses linear probing for collision resolution
 *
 *O(n)
 */
void addElement(SET *sp, char *elt){
	assert(sp!=NULL);
	int found = 0;
	int x = search(sp, elt, &found);
	if ((sp->count == sp->length)||found==1)
		return;
	int i = strhash(elt)%sp->length;
	while (sp->flags[i] == 'F'){
		i++;
		i = i%sp->length;
	}
	sp->flags[i] = 'F';
	sp->data[i] = strdup(elt);
	sp->count++;
	return;	
}

/*Removes an element identical to the elt
 *
 *O(n)
 */
void removeElement(SET *sp, char *elt){
	assert(sp!=NULL);
	assert(elt !=NULL);
	int found = 0;
	int x = search(sp, elt,&found);
	if (found == 0)
		return;
	sp->flags[x] = 'D';
	sp->data[x] = NULL;
	sp->count--;
	return;
}

/*Returns the pointer an element identical to elt.
 *
 *O(n)
 */
char *findElement(SET *sp, char *elt){
	assert(sp!=NULL);
	int x;
	int loc = search(sp, elt, &x);
	if (x == 0)
		return NULL;
	return sp->data[loc];
}

/*Returns an array of the elements in the set given
 *
 *O(n)
 */
char **getElements(SET *sp){
	assert(sp!=NULL);
	char **elts = malloc(sizeof(char *)*sp->length);
	int i;
	int count = 0;
	for (i = 0; i < sp->length; i++){
		if (sp->flags[i]=='F'){
			elts[count]= strdup(sp->data[i]);
			count++;
		}
	}
	return elts;
}






