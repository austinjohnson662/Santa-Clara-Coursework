#include <stdio.h>
#define HIGH 8


void writeArray(int *a){
	int i;
	for(i = 0; i < HIGH; i++){
		printf("%d ", a[i]);
	}
	printf("\n");
}

void readArray(int *a){
	int i;
	for (i = 0; i < HIGH; i++){
		scanf("%d", &*a);
		a++;
	}
}

void exchange(int *a, int *b){
	int t;
	t = *a;
	*a = *b;
	*b = t;
	return;
}

int partition(int *a, int y, int z){
	int i = y-1, j = z+1, x = a[y];

	while (i < j){
		do
			j = j-1;
		while(a[j]>x);

		do 
			i = i + 1;
		while (a[i] < x);
		
		if (i < j)
			exchange(&a[i], &a[j]);
	}
	return j;
}

void quicksort(int *a, int m, int n){
	int i;
	if (n > m){
		i = partition(a, m, n);
		printf("%d\n", i);
		writeArray(a);
		quicksort(a, m, i);
		quicksort(a, i+1, n);
	}
}

void main(int argc, char *argv[]){
	int numbers[HIGH];	
	readArray(numbers);
	quicksort(numbers, 0, HIGH-1);
	writeArray(numbers);	
}
