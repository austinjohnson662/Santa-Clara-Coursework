/*
Austin Johnson
COEN 11
March 12 2019
Restraunt Reservation with multiple files and encryption
*/
#include "global.h"
//Recursively deletes all nodes behind the node given in a linked list
void clearList(LIST *temp){
	if (temp == NULL)
		return;
	clearList(temp->next);
	free(temp);
	return;
}

//Gets the information for the node. Checks for duplicates. 
int insertParty(char name[LENGTH], int partysize){
	LIST *temp;
	int groupnumber;
	temp = (LIST *)malloc(sizeof(LIST));

	strcpy(temp->name, name);
	temp->size = partysize;

	if (check_duplicate(temp->name) == 1){
		printf("Duplicate name\n");
		free(temp);
		return 0;
	}
	
	int size;
	if (temp->size < 3)
		size = 0;
	else if (temp->size < 5)
		size = 1;
	else if (temp->size < 7)
		size = 2;
	else
		size = 3;
	pthread_mutex_lock(&lock);	
	if (groupsizes[size].head == NULL){
		groupsizes[size].head = temp;
		groupsizes[size].tail = temp;
		temp->next = NULL;
		
	} else {
		groupsizes[size].tail->next = temp;
		groupsizes[size].tail = temp;
	}
	temp->next = NULL;
	pthread_mutex_unlock(&lock);
	return 0;
}
//Asks for the size of deleted node. Then, it checks the head. It then checks each middle nodes. Finally it checks the tail.
int removeParty(){
	LIST *p, *q, *temp;
	int maxsize, size;
	
	printf("Size: ");
	scanf("%d", &maxsize);
	size = (maxsize-1)/2;
	if (size > 3)
		size = 3;
	p = groupsizes[size].head;
	q = p;
	
	if (p == NULL){
		printf("List is Empty\n");
		return 0;
	}
	
	//Checking head node.
	if (p->size <= maxsize){
		pthread_mutex_lock(&lock);
		printf("%s size of %d has been removed\n", p->name, p->size);
		if (p->next == NULL){
			groupsizes[size].head = NULL;
			groupsizes[size].tail = NULL;
			free(p);
		} else {
			groupsizes[size].head = p->next;
			free(p);
		}
		pthread_mutex_unlock(&lock);
		return 0;
	} else {
		if (p->next != NULL)
			p = p->next;
	}
	
	//checks middle nodes. It doesn't check the tail node.
	while(p->next != NULL){
		if (p->size <= maxsize){
			pthread_mutex_lock(&lock);
			printf("%s size of %d has been removed\n", p->name, p->size);
			q->next = p->next;
			free(p);
			pthread_mutex_unlock(&lock);
			return 0;
		}
		p = p->next;
		q = q->next;
	}
	
	//checks if the tail is smaller
	if (p->size <= maxsize){
		pthread_mutex_lock(&lock);
		printf("%s size of %d has been removed\n", p->name, p->size);
		groupsizes[size].tail = q;
		q->next = NULL;
		free(p);
		pthread_mutex_unlock(&lock);
		return 0;
	}
	printf("No parties of given size");
	return 0;
}


//travels through the list until it is NULL. At each item it displays its information
int list(){
	LIST *p;
	int i;

	for (i = 0; i < 4; i++){
		printf("Group number %d:\n", i+1);
		p = groupsizes[i].head;
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
	int checkSize, i, maxsize;
	LIST *p;

	printf("Size: ");
	scanf("%d", &checkSize);
	maxsize = (checkSize-1)/2;
	if (maxsize > 3)
		maxsize = 3;
	for (i = 0; i <= maxsize; i++){
		p = groupsizes[i].head;
		while (p != NULL){
			if (p->size <= checkSize)
				printf("name: %s Size: %d\n", p->name, p->size);
			p = p->next;
		}
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

//displays list newest to oldest
void listBack(int arraynum, LIST *disp){
	if (disp == NULL){
		return;
	}
	listBack(arraynum, disp->next);
	printf("Name: %s Size: %d\n", disp->name, disp->size);
	return;
}

//displays all names backwards
void pNameBack(char *str){
	if (*str == '\0')
		return;
	pNameBack(str+1);
	printf("%c", *str);
	return;
}


