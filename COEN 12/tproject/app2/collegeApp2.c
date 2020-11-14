#include <stdio.h>
#include <stdlib.h>
#include "setApp2.h"

#define MAXL 3001
//3001 is a prime

int strhash(int id){
	return id%1009;
}

int main (int argc, char *argv[]){
	SET *sp = createDataSet(MAXL, strhash);
	int i, age, id, prevId = 0;
	for (i = 0; i < 1000; i++){
		age = (rand()%13)+18;
		id = prevId + (rand()%2)+1;
		prevId = id;
		insertion(sp, age, id);
	}
	
	printf("\n\n");
	id = (rand()%2000)+1;
	int found = 0;
	searchID(sp, id, &found);

	id = (rand()%2000)+1;
	deletion(sp, id);

	destroyDataSet(sp);
	return 1;
}
