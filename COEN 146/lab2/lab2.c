/*COEN 146L : Lab1, part 1 SingleThreaded */
#include <stdio.h>
#include <stdlib.h>
#include <time.h> 
#include <pthread.h>

#define N 2
#define M 3
#define L 4

double matrixA[N][M], matrixB[M][L], matrixC[N][L] = {0.0};

void printMatrix(int nr, int nc, double matrix[nr][nc]);
void *rowMultiplication(void *);

int main() {
	pthread_t threads[N];
	int rownum[N];
	srand(time(NULL));
	int i, j, k = 0;
	for (i = 0; i < N; i++) {
		rownum[i] = i;
		for (j = 0; j < M; j++) {
			matrixA[i][j] = rand()%100; // rand()
		}
	}

	for (i = 0; i < M; i++) {
		for (j = 0; j < L; j++) {
			matrixB[i][j] = rand()%100; // rand()
		}
	}
   	for(i = 0; i < N; i++){
		pthread_create(&(threads[i]), NULL, rowMultiplication, (void *)&rownum[i]);
	}

	for(k = 0; k < N; k++){
		pthread_join(threads[k],NULL);
	}
		
	printf("\n\nMatrixA:\n");
	printMatrix(N, M, matrixA);
	printf("\n\nMatrixB:\n");
	printMatrix(M, L, matrixB);
	printf("\n\nMatrixC:\n");
	printMatrix(N, L, matrixC); 
	
  return 0;
}

void *rowMultiplication(void *row){
	int *i = (int *)row;
	int j,k;
	double temp;
	for(j = 0; j < L; j++){
		temp = 0;
        for (k = 0; k < M; k++)
			temp += matrixA[*i][k] * matrixB[k][j];
		
		matrixC[*i][j] = temp;
	}
}

void printMatrix(int nr, int nc, double matrix[nr][nc]) {
	int i,j;
	for (i = 0; i < nr; i++) {
		for (j = 0; j < nc; j ++) {
			printf("%lf  ", matrix[i][j]);
	    }
		printf("\n");
        }
}
