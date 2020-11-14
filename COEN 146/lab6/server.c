//Name: Austin Johnson
//Date: 11/9/2020
//Title: Lab 6. Stop and Wait for an unreliable Channel with loss
//Description: Server side of a reliable UDP protocol with potential for loss and corruption



//Explain what each library does in the context of this lab. Do we need all of them?
#include <arpa/inet.h>   //This header is for in_addr 
#include <stdio.h>  //Allows for printing
#include <stdlib.h> //Needed for atoi and randomnumber
#include <string.h> //Used for string functions but is unnecesary in this program
#include <sys/socket.h> //Used for setting up sockets
#include <time.h>
#include <unistd.h> //contains type definition for many function like gethostbyname or id or read
#include <fcntl.h> //Contains system calls for open and creat
#include <netdb.h> //Contains the host and address types
#include "lab6.h"


//add the missing functions
//******STUDENT WORK******
//******STUDENT WORK******
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
	printf("Packet{ header: { seq_ack %d, len: %d, cksum: %d }, data\"", packet.header.seq_ack, packet.header.len, packet.header.cksum);
	fwrite(packet.data, (size_t)packet.header.len, 1, stdout);
	printf("\" }\n");
}

void ServerSend(int sockfd, const struct sockaddr *address, socklen_t addrlen, int seqnum) {
    // Simulatting a chance that ACK gets lost
    if ((rand() % 10) + 1 == 0) {
        //******STUDENT WORK******
        printf("ACK lost\n");
		return;
    }
    //prepare and send the ACK
    Packet packet;
    //******STUDENT WORK******
	packet.header.seq_ack = seqnum;
	packet.header.len = 0;
	packet.header.cksum = getChecksum(packet);
	sendto(sockfd, &packet, sizeof(packet), 0, address, addrlen);
	printf("Sent ACK %d, checksum %d\n", packet.header.seq_ack, packet.header.cksum);
}

Packet ServerReceive(int sockfd, struct sockaddr *address, socklen_t *addrlen, int seqnum){
                     
    Packet packet;
    while (1) {
//        Receive a packet from the client
        //******STUDENT WORK******
		recvfrom(sockfd, &packet, sizeof(packet), 0, address, addrlen);
		logPacket(packet);

        // validate the length of the packet
        //******STUDENT WORK******
        int plength = strlen(packet.data)+1;
		if (plength == 1)
			plength = 0;
		
		if (plength != packet.header.len){
			printf("Packet length does not match\n");
		}
		

        // log what was received
        printf("Received: ");
        logPacket(packet);

        //verify the checksum and the sequence number
        if (packet.header.cksum != getChecksum(packet)) {
            printf("Bad checksum, expected %d\n", getChecksum(packet));
            //******STUDENT WORK******
            ServerSend(sockfd, address, *addrlen, !seqnum);
        } else if (packet.header.seq_ack != seqnum) {
            printf("Bad seqnum, expected %d\n", seqnum);
            //******STUDENT WORK******
            ServerSend(sockfd, address, *addrlen, !seqnum);
        } else {
            printf("Good packet\n");
            //******STUDENT WORK******
			ServerSend(sockfd, address, *addrlen, seqnum);
		break;
        }
    }

    printf("\n");
    return packet;
}

int main(int argc, char *argv[]) {
    // check arguments
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <port> <outfile>\n", argv[0]);
        return EXIT_FAILURE;
    }

    // seed the RNG
    srand((unsigned)time(NULL));

    // create a socket
    //******STUDENT WORK******
	int sockfd;
	if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0){
		perror("Failiure to make socket");
		exit(1);
	}

	struct hostent *host;
	host = gethostbyname("localhost");
	
    // initialize the server address structure
    //******STUDENT WORK******
    struct sockaddr_in address;
	address.sin_family = AF_INET;
	address.sin_port = htons(atoi(argv[1]));
	address.sin_addr = *((struct in_addr *)host->h_addr);

    // bind the socket
    //******STUDENT WORK******
	if ((bind(sockfd, (struct sockaddr *)&address, sizeof(struct sockaddr))) < 0){
		perror("Binding error");
		exit(1);
	}

    //Please answer the following questions
        //[Q1] Briefly explain what is "AF_INET" used for.
		//AF_INET is what define the internet protocol being used. It is an IPv4 protocol
	    //[Q2] Briefly explain what is "SOCK_DGRAM" used for.
	    //SOCK_DGRAM specifies that the socket is for UDP connections
        //[Q3] Briefly explain what is "htons" used for.
        //htons converts the integer into a format the host can understand.
        //[Q4] Briefly explain why bind is required on the server and not on the client.
        //This is because the client is implicitly called when the first message is sent from the clien
    
    
    
    // open file
    FILE *file = fopen(argv[2], "wb");
    if (file == NULL) {
        perror("fopen");
        return EXIT_FAILURE;
    }

    // get file contents from client and save it to the file
    int seqnum = 0;
    Packet packet;
	struct sockaddr_in clientaddr;
	socklen_t clientaddr_len = sizeof(clientaddr);
    do {
		packet = ServerReceive(sockfd, (struct sockaddr *)&address, &clientaddr_len, seqnum);
		fwrite(packet.data, 1, packet.header.len, file);
		seqnum = !seqnum;
    } while (packet.header.len != 0);

    //cleanup
    //******STUDENT WORK******
    fclose(file);
	close(sockfd);
    return 0;
}
