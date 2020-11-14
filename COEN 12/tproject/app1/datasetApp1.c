/*
Austin Johnson
COEN 12
MWF 11:45-12:50
Term project
*/
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "setApp1.h"


typedef struct set {
	int *ages;
	int *ids;
	int length;
	int count;
}SET;

int searchAge(SET *sp, int, int *);

/*creates a new set with an array of size maxElts
 *
 *O(1)
 */
SET *createDataSet(int maxElts){
	SET *sp = malloc(sizeof(SET));
	assert(sp!=NULL);
	sp->length = maxElts;
	sp->count = 0;
	sp->ages = malloc(sizeof(int)*maxElts);
	sp->ids = malloc(sizeof(int)*maxElts);
	assert(sp->ages != NULL && sp->ids !=NULL);
	return sp;
}

/*Destroys the set pointed to by sp
 *
 *O(n)
 */
void destroyDataSet(SET *sp){
	assert(sp!=NULL);
	free(sp->ids);
	free(sp->ages);
	free(sp);
	return;	
}

/*Adds the element in its sorted spot in the array
 *
 *O(n)
 */
void insertion(SET *sp, int age, int id){
	assert(sp!=NULL);
	printf("Insertion: age %d id %d\n", age, id);
	if (sp->count == sp->length){
		return;
	}
	int check = 0;
	int i, x = searchAge(sp, age, &check);
	if (check == 1)
		return;
	for (i = sp->count; i > x; i--){
		sp->ages[i]=sp->ages[i-1];
		sp->ids[i]=sp->ids[i-1];
	}
	sp->ages[x] =age;
	sp->ids[x] = id;
	sp->count++;
	return;
}

/*Removes item in set sp identical to elt
 *
 *O(n)
 */
void deletion(SET *sp, int age){
	assert(sp!=NULL);
	int i, x = 0;
	int idx = searchAge(sp, age, &x);
	if (x == 0){
		printf("Deletion unsuccessful\n");
		return;
	}
	int lo = idx, hi = idx, range = 1;
	while (lo >= 0 && sp->ages[lo-1]==age){
		lo--;
		range++;
	}
	while (hi < sp->count && sp->ages[hi+1]==age){
		hi++;
		range++;
	}	
	

	for (i = lo; i<sp->count - range; i++){	
		sp->ages[i] = sp->ages[i+range];
		sp->ids[i] = sp->ids[i+range];
	}
	printf("Deletion for age %d\n", age);
	sp->count -= range;
	return;
}

/*returs the location of the element elt in the sp->data. If none returns returns where it should be.
 * If found->set found equal to 1. Otherwise to 0
 *
 *O(logn)
 */
int searchAge(SET *sp, int age, int *found){
	assert(sp != NULL);
	
	printf("Search: Age %d ID N/A Success? ", age);
	int size = sp->count-1;
	int hi = size, lo = 0, mid;
	while (hi >= lo){
		mid = (hi + lo)/2;
		if (age > sp->ages[mid]){
			lo = mid + 1;
		} else if (age < sp->ages[mid]){
			hi = mid-1;
		} else {
			printf("y ID %d\n",sp->ids[mid]);
			*found = 1;
			return mid;
		}
	}
	printf("n\n");
	*found = 0;
	return lo;
}

/*Returns the maximum age gap
 *
 *O(1)
 */
int maxAgeGap(SET *sp){
	assert(sp!=NULL);
	int range = sp->ages[sp->count-1] - sp->ages[0];
	printf("Max age gap: %d\n", range);
	return range;
}
