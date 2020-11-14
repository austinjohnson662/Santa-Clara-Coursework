/*
Austin Johnson
COEN 11
Febuary 5 2019
Restraunt Reservation with Linked Lists
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define LENGTH 20

typedef struct party {
	int size;
	char name[LENGTH];
	struct party *next;
}LIST;

typedef struct info {
	LIST *head;
	LIST *tail;
}INFO;

INFO *groupsizes[4];
LIST *head=NULL, *tail=NULL;

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
		else if (input == 0)
			break;
		else
			printf("Invalid input\n");
	}
	return 0;
}

//Gets the information for the node. Checks for duplicates. 
int insertParty(){
	LIST *temp;
	int groupnumber;
	temp = (LIST *)malloc(sizeof(LIST));

	printf("Name: ");
	scanf("%s", temp->name);
	printf("Size: ");
	scanf("%d", &temp->size);

	if (check_duplicate(temp->name) == 1){
		printf("Duplicate name");
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
	
	if (groupsizes[size].head == NULL){
		groupsizes[size].head = temp;
		groupsizes[size].tail = temp;
		temp->next = NULL;
		
	} else {
		groupsizes[size].tail->next = temp;
		groupsizes[size].tail = temp;
	}
	
	temp->next = NULL;
	return 0;
}
//Asks for the size of deleted node. Then, it checks the head. It then checks each middle nodes. Finally it checks the tail.
int removeParty(){
	LIST *p = head, *q = head, *temp;
	int maxsize;
	
	printf("Size: ");
	scanf("%d", &maxsize);
	
	if (p == NULL){
		printf("List is Empty\n");
		return 0;
	}

	//Checking head node.
	if (p->size <= maxsize){
		printf("%s size of %d has been removed\n", p->name, p->size);
		if (p->next == NULL){
			head = NULL;
			tail = NULL;
			free(p);
		} else {
			head = p->next;
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
		tail = q;
		q->next = NULL;
		free(p);
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
	}
	return 0;
}

//loops through the list. When it finds an item smaller than the determined size it prints the information of the party.
int search_size(){
	int checkSize, i;
	LIST *p = head;

	printf("Size: ");
	scanf("%d", &checkSize);
	
	while (p != NULL){
		if (p->size <= checkSize)
			printf("name: %s Size: %d\n", p->name, p->size);
		p = p->next;
	}

	return 0;
}

//traverses through the list comparing the input name to every name inside the list. returns 1 when the input string has a duplicate string in the list. Otherwise it returns 0
int check_duplicate(char inputName[LENGTH]){
	LIST *p = head;
	while (p != NULL){
		if (strcmp(inputName, p->name) == 0)
			return 1;
		p = p->next;
	}
	return 0;
}
















