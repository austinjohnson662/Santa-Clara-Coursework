#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

#define MAX 1		//max text file size


int main(int argc, char *argv[]){
	FILE *fps, *fpd;
	fps = fopen("src.jpg", "rb");	//File pointer source
	fpd = fopen("dest.jpg","wb");	//file pointer destination
	char buffer[MAX];

	if (fps == NULL || fpd == NULL){
		printf("Cannot open file\n");
		return 0;
	}
	
	while(fread(&buffer, 1, sizeof(buffer), fps)>0){
		fwrite(&buffer, 1, sizeof(buffer), fpd);
	}
	
	fclose(fps);
	fclose(fpd);
	return 1;
}
