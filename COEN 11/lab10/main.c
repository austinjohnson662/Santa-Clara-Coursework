/*
Austin Johnson
COEN 11
March 12 2019
Restraunt Reservation with multiple files and encryption
*/
#include "global.h"

INFO groupsizes[4];
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

//forever loop of inputs 1 for input name, 2 for remove, 3 for list, 4 for list under a size, 0 for quit. Reads the file at the beginnning, and it writes the array into the file at the end.
int main(int argc, char *argv[]){
	if (argc != 4){
		printf("Not enough terms\n");
		return 0;
	}
	int input, partysize, i;
	char name[LENGTH];
	LIST *p;
	readFunction(argv[1], atoi(argv[3]));
	pthread_t thr;
	pthread_create(&thr, NULL,autosave, (void *)argv[2]);
	while (1){
		scanf("%d", &input);
		if (input == 1){
			printf("Name: ");
			scanf("%s", name);
			printf("Size: ");
			scanf("%d", &partysize);
			insertParty(name, partysize);
		} else if (input == 2)
			removeParty();
		else if (input == 3)
			list();
		else if (input == 4)
			search_size();
		else if (input == 5){
			for (i = 0; i < 4; i++){
				printf("Group %d:\n", i+1);
				listBack(i, groupsizes[i].head);
				printf("\n");
			}
		} else if (input == 6) {
			for (i = 0; i < 4; i++){
				printf("group %d:\n", i+1);
				p = groupsizes[i].head;
				while(p != NULL){
					pNameBack(p->name);
					printf("\n");
					p=p->next;
				}
				printf("\n");
			}
		} else if (input == 7) {
			read_autosave(argv[2]);
		} else if (input == 0)
			break;
		else
			printf("Invalid input\n");
	}
	pthread_cancel(thr);
	writeFunction(argv[1], atoi(argv[3]));
	for (i = 0; i < 4; i++){
		clearList(groupsizes[i].head);
		groupsizes[i].head = NULL;
	}
	return 0;
}
