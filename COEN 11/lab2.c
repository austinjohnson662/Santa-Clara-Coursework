#include <stdio.h>
#include <string.h>

int insertParty();
int removeParty();
int list();

#define SIZE 10
#define LENGTH 20

int counter = 0;
char partyName[SIZE][LENGTH];
int partySize[LENGTH];

//forever loop of inputs 1 for input name, 2 for remove, 3 for list
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

		printf("Name: ");
		scanf("%s", inputName);

		printf("Size: ");
		scanf("%d", &inputSize);
		
		strcpy(partyName[counter], inputName);
		partySize[counter] = inputSize;
		counter++;
		printf("\n");
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

	printf("Size: ");
	scanf("%d", &sizeOfParty);
	
	//looks for the first item that fits into the opening
	for (i = 0; i < counter; i++){
		if (partySize[i] <= sizeOfParty){
			partyNumber = i;
			break;
		}
	}

	//checks if a party was found then it shifts every party up
	if (partyNumber != -1){		
		printf("%s (size of %d) has been removed from list\n", partyName[partyNumber], partySize[partyNumber]);		
		
		for (j = partyNumber; j < counter; j++){
			strcpy(partyName[j],partyName[j+1]);
			partySize[j] = partySize[j+1];
		}
		counter--;
	} else
		printf("No parties small enough.");
	return 0;
}

//loops through the array until counter is hit
int list(){
	int i;
	for (i = 0; i <  counter; i++){
		printf("Name: %s Size: %d\n", partyName[i], partySize[i]);
		
	}
	return 0;
}




















