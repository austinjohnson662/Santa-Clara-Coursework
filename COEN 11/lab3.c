#include <stdio.h>
#include <string.h>

#define SIZE 10
#define LENGTH 20

typedef struct party {
	int size;
	char name[LENGTH];
}LIST;

int counter = 0;
LIST partyList[SIZE];

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

//checks if the list if full. Asks for the position name and size of the party. assigns the values to the array then it increments counter.
int insertParty(){
	if (counter != SIZE){
		char inputName[LENGTH];
		int inputSize;
		LIST *p = &partyList[counter];
		
		printf("Name: ");
		scanf("%s", inputName);

		printf("Size: ");
		scanf("%d", &inputSize);
		
		if (check_duplicate(inputName) == 0){		
			strcpy(partyList[counter].name, inputName);
			partyList[counter].size = inputSize;			
			counter++;
			printf("\n");
		} else
			printf("duplicate party");
	} else
		printf("waitlist full\n");
	return 0;
}


int removeParty(){
	//check for empty list
	if (counter == 0){
		printf("Waitlist is empty\n");
		return 0;
	}
	int sizeOfParty, i, j;
	int partyNumber = -1;
	LIST *p = &partyList[0];

	printf("Size: ");
	scanf("%d", &sizeOfParty);
	
	//loops through the array until it finds an item small enough in which case it shifts every item into its spot
	for (i = 0; i < counter; i++){
		
		if (p->size <= sizeOfParty){
			printf("%s (size of %d) has been removed\n", p->name, p->size);
			for (j = i; j < counter; j++){
				*p = *(p+1);
			}
			break;
		}
		p++;
	}
	counter--;
	return 0;
}

//loops through the array until counter is hit
int list(){
	int i;
	LIST *p = &partyList[0];
	for (i = 0; i <  counter; i++){
		printf("Name: %s Size: %d\n", p->name, p->size);
		p++;
	}
	return 0;
}

//loops through the array. When it finds an item smaller then the determined size it prints the information of the party.
int search_size(){
	int checkSize, i;
	LIST *p = &partyList[0];

	printf("Size: ");
	scanf("%d", &checkSize);
	
	for (i = 0; i < counter; i++){
		if (p->size <= checkSize)
			printf("name: %s Size: %d\n", p->name, p->size);
		p++;
	}

	return 0;
}

//loops through the array comparing the input name to every name inside the array. returns 1 when the input string is equal to a number in the array. Otherwise it returns 0
int check_duplicate(char inputName[LENGTH]){
	LIST *p = &partyList[0];
	int i;
	for (i = 0; i < counter; i++){
		if (strcmp(inputName, p->name) == 0)
			return 1;
		p++;
	}
	return 0;
}
















