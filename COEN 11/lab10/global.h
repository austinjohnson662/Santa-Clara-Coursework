/*
Austin Johnson
COEN 11
March 12 2019
Restraunt Reservation with multiple files and encryption
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

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

INFO groupsizes[4];
pthread_mutex_t lock;

int insertParty(char[], int partysize);
int removeParty();
int list();
int search_size();
int check_duplicate(char[LENGTH]);
int readFunction(char *, int);
int writeFunction(char *, int);
void listBack(int, LIST *);
void pNameBack(char *);
void clearList(LIST *);
void * autosave(void *);
void read_autosave();
