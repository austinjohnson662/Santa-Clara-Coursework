//Austin Johnson
//10/19/20
//Lab 4 P2P
//Uses a p2p protocol to transfer a file from one host to another host


//UDP Client
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

#define MAX 100

//Declare socket file descriptor. All  Unix  I/O  streams  are  referenced  by  descriptors
int sockfd;

//Declare sending and receiving buffer of size 1k bytes
char sbuf[1024],rbuf[1024];

 //Declare p2p addresses
struct sockaddr_in servAddr1, servAddr2; 
struct hostent *host;
socklen_t addrLen = sizeof(struct sockaddr);

char hostname[20], fp[20], fdst[20];

//This initialized the socket and the port numbers
void openSocket(){
	host = (struct hostent *)gethostbyname(hostname);
	if (host == NULL){
		perror("Could not find the host");
		exit(1);
	}
	
	servAddr1.sin_family = AF_INET;
	servAddr1.sin_port = htons(5001);
	servAddr1.sin_addr = *((struct in_addr *)host->h_addr);
	servAddr2.sin_family = AF_INET;
	servAddr2.sin_port = htons(5002);
	servAddr2.sin_addr = *((struct in_addr *)host->h_addr);

	if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0))<0){
		perror("Couldnt set up the socket");
		exit(1);
	}
	return;
}

//This is the protocol for when the host acts as a server
void server(){
	//initializations
	printf("Server\n");
	gethostname(hostname, 20);
	printf("Server hostname: %s\n", hostname);
	openSocket();

	if ((bind(sockfd, (struct sockaddr *)&servAddr1, sizeof(struct sockaddr))) < 0){
		perror("Couldnt bind the socket");
		exit(1);
	}

	//receives the message from the sender
	int numr;
	while((numr = recvfrom(sockfd, rbuf, 1024, 0, (struct sockaddr *)&servAddr2, &addrLen)) > 0){
		rbuf[numr] = '\0';
		printf("Client message: %s\n", rbuf);
		if (strcmp(rbuf, "REQUEST") == 0) {
			break;
		}
	}

	//opens the file and reports to the sender if there was an error retreiving the file
	int f = open(fp, O_RDWR);
	if (fp < 0){
		perror("unable to open src\n");
		sendto(sockfd, "ERROR", strlen("ERROR"), 0, (struct sockaddr *)&servAddr2, sizeof(struct sockaddr));
		exit(1);
	}

	sendto(sockfd, "SENDING", strlen("SENDING"), 0, (struct sockaddr *)&servAddr2, sizeof(struct sockaddr));

	//reads the file into the destination
	int size;
	while(0 < (size = read(f, sbuf, sizeof(sbuf))))
		sendto(sockfd, sbuf, strlen(sbuf), 0, (struct sockaddr *)&servAddr2, sizeof(struct sockaddr));

	sendto(sockfd, "EOF", strlen("EOF"), 0, (struct sockaddr *)&servAddr2, sizeof(struct sockaddr));
	close(f);
	printf("File finished\n");

	close(sockfd);
}

//For when the server acts as a client
void client(){
	//initializations
	printf("Client\n");
	printf("Enter host: \n");
	scanf("%s", hostname);	
	openSocket();

	//Handshaking
	sendto(sockfd, "REQUEST", strlen("REQUEST"), 0, (struct sockaddr *)&servAddr2, sizeof(struct sockaddr));
	printf("File Sent\n");	

	//retreives the message and checks for an error
	int numr;
	while((numr = recvfrom(sockfd, rbuf, 1024, 0, (struct sockaddr *)&servAddr2, &addrLen)) > 0){
		rbuf[numr] = '\0';
		printf("Client message: %s\n", rbuf);
		if (strcmp(rbuf, "SENDING") == 0) {
			break;
		} else if (strcmp(rbuf, "ERROR") == 0){
			perror("Unable to open the src in addr 2");
			exit(1);
		}
	}

	//Creates a file or opens it
	int f = open(fdst, O_RDWR | O_CREAT, 0777);
	if (fp < 0){
		perror("unable to open src\n");
		exit(1);
	}


	//writes the file into the 
	int size;
	while((numr = recvfrom(sockfd, rbuf, 1024, 0, (struct sockaddr *)&servAddr2, &addrLen)) > 0){
		rbuf[numr] = '\0';
		if (strcmp(rbuf, "EOF") == 0){
			printf("EOF\n");
			break;
		} else
			write(f, rbuf, strlen(rbuf));

	}
	close(f);
	printf("File finished\n");

	close(sockfd);

}


int main(){
	//Control for the function	
	while(1) { 
		char in;
		printf("Send(S), receive(R), or quit(Q)?\n");
		scanf("%c", &in);
		if (in == 'S'|| in == 's'){
			printf("Peer 1 is sending\n");
			printf("Enter Filename:\n");
			scanf("%s", fp);
			server();
		} else if (in == 'R'|| in == 'r'){
			printf("Peer 1 is receiving\n");
			printf("Enter Filename:\n");
			scanf("%s", fdst);
			client();
		} else if (in == 'Q'|| in == 'q')
			return 0;
		printf("\n");
	}
	return 0;
}
