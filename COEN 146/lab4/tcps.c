//Austin Johnson
//10/15/20
//Lab 4
//TCP Server
//This is the server portion of a TCP connection that sends a file to a client

// TCP Server
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <fcntl.h>

#define nthr 1024 //# of theads
pthread_t threads[nthr];

//This functions loops until the entire file is inserted into the destination file
void *clientFunction(void *tracker){
 int fd;
 int *i = (int *)tracker;
 int numr;
 char buf[1024];
 int connThr = *i;
 while((numr = recv(connThr, buf, nthr, 0))){
  printf("%s\n", buf);
  fd = open("dest2.dat", O_WRONLY, 0);
  write(fd, buf, numr);
  close(fd);
  if (numr == 0)
   break;
 }
}

int main(){
 //Declare socket file descriptor. All  Unix  I/O  streams  are  referenced  by  descriptors
 int sockfd, connfd, sin_size;
 
 //Declare receiving buffer of size 1k bytes
 char rbuf[1024];

 //Declare server address to which to bind for receiving messages and client address to fill in sending address
 struct sockaddr_in servAddr, clienAddr;
 socklen_t addrLen = sizeof(struct sockaddr);

 //Open a UDP socket, if successful, returns  a descriptor  associated  with  an endpoint 
 if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    perror("Failure to setup an endpoint socket");
    exit(1);
 }
 
 //Setup the server address to bind using socket addressing structure
 servAddr.sin_family = AF_INET;
 servAddr.sin_port = htons(5003); //Port 5000 is assigned
 servAddr.sin_addr.s_addr = INADDR_ANY; //Local IP address of any interface is assigned (generally one interface IP address)

 //Set address/port of server endpoint for socket socket descriptor
 if ((bind(sockfd, (struct sockaddr *)&servAddr, sizeof(struct sockaddr))) < 0){
	perror("Failure to bind server address to the endpoint socket");
    exit(1);
 }

 //listening for clients. can queue up to 5 clients.
 listen(sockfd, 5);

 sin_size = sizeof(struct sockaddr_in);
 int numr;
 int j = 0;
//Sever continuously waits for messages from client, then prints incoming messages.
 while (1){
	if ((connfd = accept(sockfd, (struct sockaddr *)&clienAddr, (socklen_t *)&sin_size)) < 0){
		perror("Failure to accept connection to the client");
		exit(1);
	}

    printf("Connection accepted \n");
	pthread_create(&threads[j], NULL, clientFunction, (void *)&connfd);
	j++;

/*	int nr = recvfrom(sockfd, rbuf, 1024, 0, (struct sockaddr *)&clienAddr, &addrLen);
	rbuf[nr] = '\0';
	printf("Client with IP: %s and Port: %d sent message: %s\n", inet_ntoa(clienAddr.sin_addr),ntohs(clienAddr.sin_port), rbuf);*/

 }
 
 printf("Connection clients: IP %s port %d\n", inet_ntoa(clienAddr.sin_addr), ntohs(clienAddr.sin_port));
 close(connfd);
 close(sockfd);

 return 0;
}
