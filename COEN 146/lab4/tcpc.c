//Austin iJohnson
//10/15/20
//Lab 4
//Server client tcp connection with concurrent connections


//TCP Client
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#define SIZE 100

int main(){
 //Declare socket file descriptor. All  Unix  I/O  streams  are  referenced  by  descriptors
 int sockfd; 

 //Declare sending and receiving buffer of size 1k bytes
 char sbuf[1024], rbuf[1024]; 
 
 //Declare server address to 
 struct sockaddr_in servAddr;

 //Converts  domain  names   into  numerical  IP  addresses  via  DNS
 struct hostent *host;
 host = (struct hostent *)gethostbyname("localhost"); //Local host runs the server. You may use "127.0.0.1": loopback IP address
 
 //Open a socket, if successful, returns  a descriptor  associated  with  an endpoint 
 if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    perror("Failure to setup an endpoint socket");
    exit(1);
 }

 //Set the server address to send using socket addressing structure
 servAddr.sin_family = AF_INET;
 servAddr.sin_port = htons(5003);
 servAddr.sin_addr = *((struct in_addr *)host->h_addr);


if (connect(sockfd, (struct sockaddr *)&servAddr, sizeof(struct sockaddr))){
  perror("Failure to connect to the server");
  exit(1);
}

//declarations for sending
 FILE *fp;
 int numr;
 char fbuf[SIZE];

 //Client to send messages to the server continuously using UDP socket 
 while(1){
  printf("Client: What file do you want to send?\n");
  scanf("%s", sbuf);

  fp = fopen(sbuf, "r");
  if (sbuf == NULL){
   printf("Could not find the file\n");
   exit(1);
  }
 
//keeps reading the file until it reaches the end 
  while(!feof(fp)){
   numr = fread(&fbuf, 1, 1, fp);
   if (!feof(fp))
	printf("%s", fbuf);
   send(sockfd, fbuf, strlen(fbuf), 0);
  }
  printf("\n");
  fclose(fp);
  printf("File sent\n");
 }

 //closes the socket
 close(sockfd);

 return 0;
}
