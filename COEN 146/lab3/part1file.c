#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define MAX 100		//max text file size


int main(int argc, char *argv[]){
	FILE *fps, *fpd;
	fps = fopen("src.txt", "r");	//File pointer source
	fpd = fopen("dest.txt","w");	//file pointer destination
	
	if (fps == NULL || fpd == NULL){
		printf("Cannot open file\n");
		return 0;
	}

	char c = fgetc(fps);
	while (c  != EOF){
		fputc(c, fpd);
		c = fgetc(fps);
	} 

	fclose(fps);
	fclose(fpd);
	return 1;
}
