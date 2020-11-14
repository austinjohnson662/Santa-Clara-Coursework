//Name: Austin Johnson
//Date: 11/2/2020
//Title: Lab5 - client
//Description: This program is meant to take a file and send the file to a server program for it to be copied into an out file.
//This program utilizes TFv2 to ensure reliable transmission


#include <arpa/inet.h>
#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <time.h>
#include <unistd.h>
#include <netdb.h>
#include <netinet/in.h>
#include "lab5.h"

int seq = 0;

// NOTE: beware of sign extension if the checksum is stored in a char, then converted to an int!
int getChecksum(Packet packet) {
    packet.header.cksum = 0;

    int checksum = 0;
    char *ptr = (char *)&packet;
    char *end = ptr + sizeof(Header) + packet.header.len;

//Please find an error from the remaining part getChecksum() function 
//******STUDENT WORK****** 
    while (ptr < end) {
        checksum ^= *ptr++;
    }

    return checksum;
}

void logPacket(Packet packet) {
    printf("Packet{ header: { seq_ack: %d, len: %d, cksum: %d }, data: \"",
            packet.header.seq_ack,
            packet.header.len,
            packet.header.cksum);
    fwrite(packet.data, (size_t)packet.header.len, 1, stdout);
    printf("\" }\n");
}



void ClientSend(int sockfd, struct sockaddr *address, socklen_t addrlen, Packet packet) {
	int num = 0;
    while (1) {

        // send the packet
		printf("Sending packet\n");
		//******STUDENT WORK******
		logPacket(packet);
		sendto(sockfd, &packet, sizeof(packet), 0, address, addrlen);
		printf("Sent\n");


        // receive an ACK from the server
        Packet recvpacket;
		//******STUDENT WORK******
		printf("Recv packet: \n");
		recvfrom(sockfd, &recvpacket, 1024, 0, address, &addrlen);
	//	logPacket(recvpacket);
			
        // log what was received
        printf("Received ACK %d, checksum %d - \n", recvpacket.header.seq_ack, recvpacket.header.cksum);
        // validate the ACK
        if (recvpacket.header.cksum != getChecksum(recvpacket)) {
            // bad checksum, resend packet
            printf("Bad checksum, expected checksum was: %d\n", getChecksum(recvpacket));
        } else if (recvpacket.header.seq_ack != seq) {
            // incorrect sequence number, resend packet
            printf("Bad seqnum, expected sequence number was: %d\n", seq);
        } else {
            // good ACK, we're done
            printf("Good ACK\n");
			seq = !seq;
            break;
        }
		//fixes any error
		packet.header.cksum = getChecksum(packet);
    }

    printf("\n");
}

int main(int argc, char *argv[]) {
    // check arguments
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <ip> <port> <infile>\n", argv[0]);
        return 1;
    }

    // seed the RNG
    srand((unsigned)time(NULL));

    // create and configure the socket [name the socket sockfd] 
	int sockfd;
	if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0))<0){
		perror("Socket failiure");
		exit(1);
	}
    // initialize the server address structure using argv[2] and argv[1]
    struct sockaddr_in address;
    memset(&address, 0, sizeof(address));

	struct hostent *host;
	host = (struct hostent *)gethostbyname(argv[1]);
	socklen_t addrlen = sizeof(address);

	address.sin_family = AF_INET;
	address.sin_port = htons(atoi(argv[2]));
	address.sin_addr = *((struct in_addr *)host->h_addr);
	//******STUDENT WORK******

    // open file using argv[3]
	int fp;
	fp = open(argv[3], O_RDWR);
	//******STUDENT WORK******

    // send file contents to server
	//-create a packet
	//-set the seq_ack field 
	//-set the len field
	//-calculate the checksum
	//-send the packet
	Packet p1;
	int buffer = 1;
	while((buffer = read(fp, p1.data, sizeof(p1.data))) != 0){
		//set the packet and randomize for potential loss
		p1.header.seq_ack = seq;
		p1.header.len = buffer;
		int randomnumber = rand()%(100) + 1;
		printf("Random number: %d\n", randomnumber);
		if (randomnumber < 75){
			p1.header.cksum = getChecksum(p1);
		} else {
			p1.header.cksum = 100;
		}
		ClientSend(sockfd,(struct sockaddr *)&address, sizeof(struct sockaddr), p1);
	}
	//******STUDENT WORK******
    // send zero-length packet to server to end connection
	p1.header.seq_ack = seq;
	p1.header.len = 0;
	p1.header.cksum = getChecksum(p1);
	ClientSend(sockfd,(struct sockaddr *)&address, sizeof(struct sockaddr), p1);
	//******STUDENT WORK******

    // clean up
	//-close the sockets and file
	//******STUDENT WORK******
	close(fp);
	close(sockfd);

    return 0;
}
