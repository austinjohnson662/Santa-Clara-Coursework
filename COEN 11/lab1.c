#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int division();
int main(){

	//creates randomness
	srand((int) time(NULL));
	int totalCorrect = 0, denominator, quotient;
	
	//handles each individual division inside the loop
	for (int i=0; i<10; i++){
		denominator = rand()%12 + 1;
		quotient = rand()%13;
		totalCorrect = totalCorrect + division(denominator, quotient);
	}
	printf("You got %d0 percent right\n", totalCorrect);
	return 0;
}

int division(int denominator,int quotient){
	int dividend, answer;
	
	dividend = denominator*quotient;
	
	//print the question
	printf("%d/%d=?\n",dividend,denominator);
	
`	//looks for the answer
	scanf("%d",&answer);
	if (answer == quotient){
		printf("Correct!\n");
		return 1;
	}
	printf("Incorrect. The answer was %d\n", quotient);
	return 0;
}
