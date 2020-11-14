#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "list.h"

typedef struct node {
	void *data;
	struct node *next;
	struct node *prev;
}NODE;

typedef struct list {
	NODE *head;
	int count;
	int (*compare)();
}LIST;
//initializes list
//O(1)
LIST *createList(int (*compare)()){
	LIST *lp;
	lp = malloc(sizeof(LIST));
	assert(lp != NULL);
	lp->head = malloc(sizeof(NODE));
	assert(lp->head != NULL);
	lp->head->data = NULL;
	lp->head->next = lp->head;
	lp->head->prev = lp->head;
	lp->compare = compare;
	lp->count = 0;
	return lp;
}
//destroys all memory allocated
//O(n)
void destroyList(LIST *lp){
	NODE *np, *pnext;
	assert(lp!=NULL);
	np = lp->head;
	do {
		pnext = np->next;
		free(np);
		np = pnext;
	} while (np != lp->head);
	free(lp);
	return;
}
//returns num of items
//O(1)
int numItems(LIST *lp){
	assert(lp != NULL);
	return lp->count;
}
//adds item to the first spot
//O(1)
void addFirst(LIST *lp, void *item){
	assert(lp!=NULL);
	NODE *temp = malloc(sizeof(NODE));
	assert(temp != NULL);
	temp->data = item;
	temp->next = lp->head->next;
	lp->head->next->prev=temp;
	lp->head->next = temp;
	temp->prev = lp->head;
	temp->next->prev = temp;
	return;
}
//adds item to the last spot
//O(1)
void addLast(LIST *lp, void *item){
	assert(lp!=NULL);
	NODE *temp = malloc(sizeof(NODE));
	assert(temp != NULL);
	temp->data = item;
	temp->next = lp->head;
	temp->prev = lp->head->prev;
	lp->head->prev->next = temp;
	lp->head->prev = temp;
	lp->count++;
	return;
}
//removes item in the first spot
//O(1)
void *removeFirst(LIST *lp){
	assert(lp != NULL && lp->count > 0);
	NODE *temp = lp->head->next;
	void* data = temp->data;
	lp->head->next = temp->next;
	temp->next->prev = lp->head;
	free(temp);
	lp->count--;
	return data;
}
//removes item in the last press
//O(1)
void *removeLast(LIST *lp){
	assert(lp != NULL && lp->count >0);
	NODE *temp = lp->head->prev;
	void* data = temp->data;
	lp->head->prev = temp->prev;
	temp->prev->next = lp->head;
	free(temp);
	lp->count--;
	return data;
}
//returns value of first elt
//O(1)
void *getFirst(LIST *lp){
	assert(lp != NULL);
	return lp->head->next->data;
}
//returns value of last elt
//O(1)
void *getLast(LIST *lp){
	assert(lp != NULL);
	return lp->head->prev->data;
}
//removes item identical to item
//O(n)
void removeItem(LIST *lp, void *item){
	assert((lp!=NULL)&&(item != NULL));
	NODE *pnow = lp->head->next;
	while (pnow != lp->head){
		if ((*lp->compare)(pnow->data, item) == 0){
			pnow->prev->next = pnow->next;
			pnow->next->prev = pnow->prev;
			free(pnow);
			lp->count -= 1;
			return;
		}
		pnow = pnow->next;
	}
	return;
}
//returns point to element identical to item
//O(n)
void *findItem(LIST *lp, void *item){
	assert((lp!=NULL)&&(item != NULL));
	NODE *pnow = lp->head->next;
	while (pnow != lp->head){
		if ((*lp->compare)(pnow->data, item)==0){
			return pnow->data;
		}
		pnow= pnow->next;
	}
	return NULL;
}
//returns the array of items in the list
//O(n)
void *getItems(LIST *lp){
	assert(lp != NULL&&lp->count>0);
	void **items = malloc(sizeof(void *)*lp->count);
	NODE *cur = lp->head->next;
	int i=0;
	do {
		items[i] = cur->data;
		cur = cur->next;
		i++;
	}while (cur != lp->head);
	return items;
}
















