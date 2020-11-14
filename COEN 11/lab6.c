/*
Austin Johnson
COEN 11
Febuary 5 2019
Restraunt Reservation with an array of linked lists
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define LENGTH 20

//contains information for each party and also refers to the next person in line
typedef struct party {
	int size;
	char name[LENGTH];
	struct party *next;
}LIST;

//Head and tail pointer for every size group list
typedef struct info {
	LIST *head;
	LIST *tail;
}INFO;

INFO groupsizes[4] = {{NULL, NULL}, {NULL, NULL}, {NULL, NULL}, {NULL, NULL}};

int insertParty();
int removeParty();
int list();
int search_size();
int check_duplicate(char[LENGTH]);

//forever loop of inputs 1 for input name, 2 for remove, 3 for list, 4 for list under a size, 0 for quit
int main(){
	int input;
	while (1){
		scanf("%d", &input);
		if (input == 1)
			insertParty();
		else if (input == 2)
			removeParty();
		else if (input == 3)
			list();
		else if (input == 4)
			search_size();
		else if (input == 0){
			LIST *p, *q;
			int i;
			for (i = 0; i < 4; i++){
				p = groupsizes[i].head;
				q = p;
				while (p != NULL){
					q = q->next;
					free(p);
					p = q;
				}
			}
			break;
		} else
			printf("Invalid input\n");
	}
	return 0;
}

//Gets the information for the node. Checks for duplicates. 
int insertParty(){
	LIST *temp;
	temp = (LIST *)malloc(sizeof(LIST));
	int size = -1;

	printf("Name: ");
	scanf("%s", temp->name);
	printf("Size: ");
	scanf("%d", &temp->size);

	if (temp->size < 3)
		size = 0;
	else if (temp->size < 5)
		size = 1;
	else if (temp->size < 7)
		size = 2;
	else
		size = 3;

	if (check_duplicate(temp->name) == 1){
		printf("Duplicate name\n");
		free(temp);
		return 0;
	}
	if (groupsizes[size]->head == NULL){
		groupsizes[size]->head = temp;
		groupsizes[size]->tail = temp;
		temp->next = NULL;

	} else {
		groupsizes[size]->tail->next = temp;
		groupsizes[size]->tail = temp;
	}
	
	temp->next = NULL;
	return 0;
}
//Asks for the size of deleted node. Then, it checks the head. It then checks each middle nodes. Finally it checks the tail.
int removeParty(){
	LIST *temp, *p, *q;
	int maxsize, size_select, i;

	printf("Size: ");
	scanf("%d", &maxsize);
	size_select = (maxsize-1)/2;
	if (size_select > 4)
		size_select = 4;

	if (groupsizes[0].head == NULL && groupsizes[1].head == NULL && groupsizes[2].head == NULL && groupsizes[3].head == NULL){
		printf("List is Empty\n");
		return 0;
	}
	for (i = 0; i <= size_select; i++){
		p = groupsizes[i].head;
		q = p;
		if (p != NULL){
			//Checking head node.
			if (p->size <= maxsize){
				printf("%s size of %d has been removed\n", p->name, p->size);
						if (p->next == NULL){
							groupsizes[i].head = NULL;
					groupsizes[i].tail = NULL;
					free(p);
				} else {
					groupsizes[i].head = p->next;
					free(p);
				}
				return 0;
			} else {
				if (p->next != NULL)
					p = p->next;
			}
			//checks middle nodes. It doesn't check the tail node.
			while(p->next != NULL){
				if (p->size <= maxsize){
					printf("%s size of %d has been removed\n", p->name, p->size);
					q->next = p->next;
					free(p);
					return 0;
				}
				p = p->next;
				q = q->next;
			}
	
			//checks if the tail is smaller
			if (p->size <= maxsize){
				printf("%s size of %d has been removed\n", p->name, p->size);
				groupsizes[i].tail = q;
				q->next = NULL;
				free(p);
				return 0;
			}
		}
	}
	printf("No parties of given size\n");
	return 0;
}


//travels through the list until it is NULL. At each item it displays its information
int list(){
	LIST *p;
	int i;
	
	for (i = 0; i < 4; i++){
		p = groupsizes[i].head;
		printf("Group %d:\n", i+1);
		while (p != NULL){
			printf("Name: %s Size: %d\n", p->name, p->size);
			p = p->next;
		}
		printf("\n");
	}
	return 0;
}

//loops through the list. When it finds an item smaller than the determined size it prints the information of the party.
int search_size(){
	int checkSize, i, max;
	LIST *p;
	
	printf("Size: ");
	scanf("%d", &checkSize);
	if (checkSize < 3)
		max = 1;
	else if (checkSize < 5)
		max = 2;
	else if (checkSize < 7)
		max = 3;
	else 
		max = 4;

	for (i = 0; i < max; i++){
		p = groupsizes[i].head;
		printf("Group %d: \n", i+1);
		while (p != NULL){
			if (p->size <= checkSize)
				printf("name: %s Size: %d\n", p->name, p->size);
			p = p->next;
		}
		printf("\n");
	}
	return 0;
}

//traverses through the list comparing the input name to every name inside the list. returns 1 when the input string has a duplicate string in the list. Otherwise it returns 0
int check_duplicate(char inputName[LENGTH]){
	LIST *p;
	int i;
	for (i = 0; i < 4; i++){
		p = groupsizes[i].head;
		while (p != NULL){
			if (strcmp(inputName, p->name) == 0)
				return 1;
			p = p->next;
		}
	}
	return 0;
}
















