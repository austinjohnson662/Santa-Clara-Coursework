#include <stdio.h>
#include <stdlib.h>
#include "setApp1.h"

#define MAXL 3000

int main (int argc, char *argv[]){
	
	SET *sp = createDataSet(MAXL);
	int i, age, id, prevId = 0;
	for (i = 0; i < 1000; i++){
		age = (rand()%13)+18;
		id = prevId + (rand()%2)+1;
		prevId = id;
		insertion(sp, age, id);
	}
	
	printf("\n\n");
	age = (rand()%13)+18;
	int found =0;
	searchAge(sp, age, &found);
	deletion(sp, age);
	

	int ageGap = maxAgeGap(sp);
	destroyDataSet(sp);
	return 1;
}
