#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "setApp2.h"


typedef struct set {
	int count;
	int length;
	int *ages;
	int *ids;
	char* flags;
	int (*hash)();
}SET;

/*Searches for an element. If found the location is returned and found is set to 1. Otherwise, returns -1 and found is set to 0.
 *
 * O(n)(big O is dependent on the runtime of *sp->hash)
 */
int searchID(SET *sp, int id, int *found){
	assert(sp!=NULL);
	int i = (*sp->hash)(id)%sp->length;
	int start = i, delx = -1;;
	while (sp->flags[i] != 'E'){
		if (sp->flags[i]== 'F'){
			if (id == sp->ids[i]){
				printf("SearchID: Found id %d\n",id);
				*found = 1;
				return i;
			}
		} else if (sp->flags[i] == 'D'){
			if (delx == -1) delx = i;
		}
		i++;
		i = i % sp->length;
		if (i == start){
			*found = 0;
			break;
		}
	}
	printf("SearchID: not found id %d\n",id);
	*found = 0;
	return i;
}

/*Creates a set. Compare and hash function are set as paramenters
 *
 *O(n)
 */
SET *createDataSet(int maxElts, int (*hash)()){
	SET *sp = malloc(sizeof(SET));
	assert(sp!=NULL);
	sp->count = 0;
	sp->length = maxElts;
	sp->ages = malloc(sizeof(int)*maxElts);
	sp->ids = malloc(sizeof(int)*maxElts);
	sp->flags = malloc(sizeof(char)*maxElts);
	assert(sp->flags != NULL && sp->ages != NULL);
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
void destroyDataSet(SET *sp){
	assert(sp!=NULL);
	free(sp->flags);
	free(sp->ages);
	free(sp->ids);
	free(sp);
	return;
}

/*Adds an elements to the hashed location, and if it cannot it will prob until an empty spot can be found.
 *
 *O(n)
 */
void insertion(SET *sp, int age, int id){
	assert(sp!=NULL);
	int found = 0;
	int i = searchID(sp, id, &found);
	if ((sp->count == sp->length)||found==1)
		return;
	sp->flags[i] = 'F';
	sp->ages[i] = age;
	sp->ids[i] = id;
	sp->count++;
	return;	
}

/*Removes an element identical to the value of elt
 *
 *O(n)
 */
void deletion(SET *sp, int id){
	assert(sp!=NULL);
	int found = 0;
	int x = searchID(sp, id,&found);
	if (found == 0){
		printf("Deletion Unsuccessful\n");
		return;
	}
	printf("Deletion Successful for age %d id %d\n", sp->ages[x], sp->ids[x]);
	sp->flags[x] = 'D';
	sp->count--;
	return;
}

