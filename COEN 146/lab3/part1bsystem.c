#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define MAX 1

int main(int argc, char *argv[]){
	int fs = open("src.jpg", O_RDWR | O_CREAT);
	int fd = open("dest.jpg", O_RDWR | O_CREAT);
	char buffer[MAX];
	if (fs == -1){
		printf("could not open file\n");
		return 0;
	}
	
	while(read(fs, buffer, MAX)>0){
		write(fd, buffer, MAX);
	}

	close(fd);
	close(fs);
}
