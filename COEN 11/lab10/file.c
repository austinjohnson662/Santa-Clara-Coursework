/*
Austin Johnson
COEN 11
March 12 2019
Restraunt Reservation with multiple files and encryption
*/
#include "global.h"
void read_autosave(char *filename){
	pthread_mutex_lock(&lock);
	int i;
	LIST temp;
	FILE *fp;
	if ((fp = fopen(filename, "rb"))==NULL){
		printf("Error opening file");
		pthread_mutex_unlock(&lock);
		return;
	}

	while (fread(&temp, sizeof(LIST), 1, fp) == 1){
		printf("%s\t%d\n", temp.name, temp.size);
	}
	
	fclose(fp);
	pthread_mutex_unlock(&lock);
	return;
}
void * autosave(void *name){
	FILE *fp;
	int i;
	LIST *p;
	while(1){
		pthread_mutex_lock(&lock);
		fp = fopen(name, "wb");
		for (i=0; i<4; i++){
			p = groupsizes[i].head;
			while (p != NULL){
				fwrite(p, sizeof(LIST), 1, fp);
				p=p->next;
			}
		}
		fclose(fp);
		pthread_mutex_unlock(&lock);
		printf("Autosave\n");
		sleep(15);
	}
	return NULL;	
}

//loops through the array and then it prints into the file
int writeFunction(char *filename, int encrypt){
	LIST *p;
	FILE *fp = fopen(filename, "w");
	int i, j;
	char datainput[200], *charp;
	printf("Test1\n");
	for (i = 0; i < 4; i++){
		p = groupsizes[i].head;
		while (p!=NULL){
			printf("test2\n");
			sprintf(datainput, "%s\t%d\n", p->name, p->size);
			charp = datainput;
			printf("Test3\n");
			while(*charp!='\n'){
				printf("Loop\n");
				*charp = *charp ^ encrypt;
				charp++;
			}
			printf("Test4\n");
			fprintf(fp, "%s",datainput);
			p = p->next;
			
		}
	}
	fclose(fp);
	return 0;
}
//looks at the file starting after the header and it scans each line
int readFunction(char *filename, int encrypt){
	char name[LENGTH];
	int partysize, i;
	char input[200], *charp;
	printf("Hello1\n");
	FILE *fp = fopen(filename, "r");
	if (fp != NULL){
		printf("Hello2\n");
		while ((fgets(input,200,fp))!=NULL){
			charp = input;
			printf("Error?\n");
			while(*charp!='\n'){
				printf("Loop\n");
				*charp = *charp ^ encrypt;
				charp++;
			}
			printf("\nHello3\n");
			sscanf(input, "%s\t%d\n", name, &partysize);
			printf("Hello4\n");
			insertParty(name, partysize);
			list();
		}
	} else {
		printf("List initially empty\n");
	}
	fclose(fp);
	return 0;
}


