#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <ctype.h>
#include "pqueue.h"
#include "pack.h"


//function given by TA's to make nodes
//
//O(1)
static struct node *mknode(int data,struct node *left, struct node *right){
	struct node  *np;
	np = malloc(sizeof(struct node));
	np->count = data;
	np->parent = NULL;
	if (left != NULL)
		left->parent = np;
	if (right != NULL)
		right->parent = np;
	return np;
}
//compare function for priority queue
//
//O(1)
int intcmp(struct node *n1, struct node  *n2){
	if (n1->count > n2->count)
		return 1;
	if (n2->count > n1->count)
		return -1;
	return 0;
}

//prints the total bits each character uses
//
//O(1)
void printTree(struct node **leaves, int *counts){
	int i, freq;
	struct node *np;
	for (i = 0; i<257; i++){
		if (leaves[i]!=NULL){
			np = leaves[i];
			freq = 0;
			while (np->parent !=NULL){
				np = np->parent;
				freq++;
			}
			if (isprint(i)!=0){
				printf("'%c': %d x %d bits = %d bits\n",(char)i, counts[i], freq, freq*counts[i]);
			} else {
				printf("'%03o': %d x %d bits = %d bits\n", i, counts[i], freq,freq*counts[i]);
			}
		}
	}
	return;
}

//compresses a given text file to an output file i.e.input.txt output.txt
//
//O(nlogn)
int main(int argc, char *argv[]){
	if (argc <3){
		printf("Insufficient terms (no input or output file)\n");
		return 0;
	}

	char *nInput = argv[1];
	char *nOutput = argv[2];
	FILE *fpr;
	fpr = fopen(nInput, "r");
	assert(fpr != NULL);
	int counts[257]={0};
	int i = 0, c;
	
	//records the frequency of each character in the array
	while (1){
		c = fgetc(fpr);
		if (feof(fpr))
			break;
		counts[c]++;
		i++;
	}
	fclose(fpr);
	
	//initializes the array as NULLs
	PQ *pq = createQueue(intcmp);
	struct node *leaves[257] = {0};
	for (i = 0; i < 256; i++){
		leaves[i] = NULL;
	}

	//adds the nodes to the priority queue
	for (i = 0; i < 256; i++){
		if (counts[i]>0){
			leaves[i] = mknode(counts[i], NULL, NULL);
			addEntry(pq, leaves[i]);
		}
	}

	//adds the \0 to the array
	leaves[256] = mknode(0, NULL, NULL);
	addEntry(pq, leaves[256]);
	struct node *child1, *child2, *parent;

	//forms the huffman tree
	while (numEntries(pq)>1){
		child1 = removeEntry(pq);
		child2 = removeEntry(pq);
		parent = mknode((child1->count)+(child2->count), child1, child2);
		addEntry(pq, parent);
	}

	//calls the compression program and destroys allocated memory
	pack(nInput, nOutput, leaves);
	printTree(leaves, counts);
	destroyQueue(pq);
	for (i = 0; i < 257; i++){
		if (leaves[i]!=NULL)
			free(leaves[i]);
	}

	return 1;
} 
