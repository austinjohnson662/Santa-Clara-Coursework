//Name: Austin Johnson
//Date: 11/9/2020
//Title: Lab 6. Stop and Wait for an unreliable Channel with loss
//Description: Client side of a reliable UDP connection with the potential for loss and corruption

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
#include "lab6.h"

int seq = 0;

int getChecksum(Packet packet){
	packet.header.cksum = 0;
	int sum = 0;
	char *ptr = (char *)&packet;
	char *end = ptr + sizeof(Header) + packet.header.len;
	while (ptr < end) {
		sum ^= *ptr++;
	}
	return sum;
}

void logPacket(Packet packet){
	printf("Packet{ header: {seqack: %d, len: %d, cksum: %d }, data \"", packet.header.seq_ack, packet.header.len, packet.header.cksum);
	fwrite(packet.data, (size_t)packet.header.len, 1, stdout);
	printf("\" }\n");
}

void ClientSend(int sockfd, const struct sockaddr *address, socklen_t addrlen, Packet packet, unsigned retries) {
    int count = 0;
	while (1) {
		// calculate the checksum
		//******STUDENT WORK******
		// log what is being sent
		printf("Created: ");
		logPacket(packet);
		packet.header.cksum = getChecksum(packet);
		
		// Simulate lost packet.
		int randomnumber = rand()%100;
		if (randomnumber < 10) {
		    printf("Dropping packet\n");
		} else {
			sendto(sockfd, &packet, sizeof(packet), 0, address, addrlen);
			printf("Packet send: ");
			logPacket(packet);
		    //******STUDENT WORK******
		}
       //}

        // wait until either a packet is received or timeout, i.e using the select statement
        struct timeval tv;
        int rv;

		fd_set readfds;
		fcntl(sockfd, F_SETFL, O_NONBLOCK);
		
		FD_ZERO(&readfds);
		FD_SET(sockfd, &readfds);

		tv.tv_sec = 0;
		tv.tv_usec = 500000;
        //******STUDENT WORK******
		rv = select(sockfd + 1, &readfds, NULL, NULL, &tv);
		//rv =1;		
		printf("RV: %d\n", rv);
		if (count >= retries-1){
			printf("Count break\n");
			break;
		}
		
		if (rv == 0){
			printf("Timeout\n");
			count++;
		} else /*if( rv == 1)*/{
	        // receive an ACK from the server
	        Packet recvpacket;
	        //******STUDENT WORK******
			recvfrom(sockfd, &recvpacket, sizeof(recvpacket), 0, NULL, NULL);

			
	        // log what was received
	        printf("Received ACK %d, checksum %d - ", recvpacket.header.seq_ack, recvpacket.header.cksum);
	        // validate the ACK
	        if (recvpacket.header.cksum != getChecksum(recvpacket)) {
	            // bad checksum, resend packet
	            printf("Bad checksum, expected %d\n", getChecksum(recvpacket));
				ClientSend(sockfd, address, addrlen, packet, retries);
	        } else if (packet.header.seq_ack != seq) {
	            // incorrect sequence number, resend packet
	            printf("Bad seqnum, expected %d\n", packet.header.seq_ack);
				ClientSend(sockfd, address, addrlen, packet, retries);
	        } else {
	            // good ACK, we're done
	            printf("Good ACK\n");
				seq = !seq;
	            break;
	        }
		}
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

    // create and configure the socket
    //******STUDENT WORK******
    int sockfd;

	if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0){
		perror("Failiure to setup an endpoint socket");
		exit(1);
	}
    // initialize the server address structure
    //******STUDENT WORK******
    // open file

	struct sockaddr_in servAddr;
	struct hostent *host;
	host = (struct hostent *)gethostbyname(argv[1]);
	servAddr.sin_family = AF_INET;
	servAddr.sin_port = htons(atoi(argv[2]));
	servAddr.sin_addr = *((struct in_addr *)host->h_addr);

    FILE *file = fopen(argv[3], "rb");
    if (file == NULL) {
        perror("fopen");
        return 1;
    }

    // send file contents to server
    Packet packet;
	int buffer;
    //******STUDENT WORK******
	while((buffer = fread(packet.data, sizeof(packet.data), 1, file)) != 0){
		//printf("buffer: %d \n", buffer);
		//printf("packet.data: %s \n", packet.data);		
		packet.header.seq_ack = seq;
		packet.header.len = strlen(packet.data);
		packet.header.cksum = getChecksum(packet);
		ClientSend(sockfd, (struct sockaddr *)&servAddr, sizeof(servAddr), packet, 3);
	}

    // send zero-length packet to server to end connection according the description provided in the Lab manual
    //******STUDENT WORK******
	packet.header.seq_ack = seq;
	packet.header.len = 0;
	packet.header.cksum = getChecksum(packet);
	ClientSend(sockfd, (struct sockaddr *)&servAddr, sizeof(servAddr), packet, 3);

    // clean up
    //******STUDENT WORK******
    fclose(file);
	close(sockfd);
    return 0;
}
