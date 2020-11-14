#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define MAX 100

int main(int argc, char *argv[]){
	int fs = open("src.txt", O_RDONLY | O_CREAT);
	int fd = open("dest.txt", O_WRONLY | O_CREAT);
	char buffer[100];
	if (fs == -1){
		printf("could not open file\n");
		return 0;
	}
	
	read(fs, buffer, MAX);
	write(fd, buffer, MAX);

	close(fd);
	close(fs);
}
