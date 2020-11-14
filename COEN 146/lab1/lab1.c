/*COEN 146L : Lab1 */
//Edited by Austin Johnson
//Uses threads instead of child processes

#include <stdio.h>      /* printf, stderr */
#include <sys/types.h>  /* pid_t */
#include <unistd.h>     /* fork */
#include <stdlib.h>     /* atoi */
#include <errno.h>      /* errno */
#include <pthread.h>

//Uses code from the sample to print
//Thread1's code 
void *thread1(void *n){
	int i, *wait = (int *)n;
	for (i = 0; i < 100; i++){
		printf("\t \t \t Thread 1: %d\n",i);
		usleep(*wait);
	}
	return 0;
}

//Thread2's code
void *thread2(void *n){
	int i, *wait = (int *)n;
   
	 for (i=0;i<100;i++) {
		printf("Thread 2: %d\n",i);
        usleep(*wait);
	}
	return 0;
}
/* main function with command-line arguments to pass */
int main(int argc, char *argv[]) {
    pid_t  pid;
	pthread_t p1, p2;
    int i, n = atoi(argv[1]); // n microseconds to input from keyboard for delay
	
	//creates the threads
	pthread_create(&p1, NULL, thread1, &n);
	pthread_create(&p2, NULL, thread2, &n);
	
	//waits for them to finish before returning
	pthread_join(p1, NULL);
	pthread_join(p2, NULL);

    return 0;
}

