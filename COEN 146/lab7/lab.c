/*
 * Link State Routing
 * Lab 7
 * 
 * Name: Austin Johnson
 * Date: 11/16/2020
 * Title: Lab 7. Link State Routing
 * Description: Utilizes link state routing to determine the cost of the least cost path between every node.
 */

#include <unistd.h>
#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <netdb.h>
        // Import the required libraries
        //******STUDENT WORK******


//defines
#define	N			4
#define	INFINITE	1000



// types
typedef struct machines
{
	//student work
	char name[50];
	char ip[50];
	int port;

} MACHINES;


// global variables
MACHINES	machines[N];
int			costs[N][N];
int			distances[N];
int			myid, nodes;
int			sock;
struct sockaddr_in addr;
struct sockaddr_in otheraddr;
socklen_t addr_size;
pthread_mutex_t	lock;
socklen_t addrlen = sizeof(struct sockaddr);


// functions
void *run_link_state (void *);
void *receive_info (void *);
void print_costs (void);


/**********************
 * main
 **********************/
int
main (int argc, char *argv[])
{
	FILE	*fp;
	int		i, j;
	pthread_t	thr1, thr2;
	int		id, cost;
	int		packet[3];


	if (argc < 5)
	{
		// check the number of arguments
        //******STUDENT WORK******
		printf("Arguement error: <myID> <#nodes> <machinefile> <costsfile>\n");
		return 0;
	}

	myid = atoi(argv[1]);
	nodes = atoi(argv[2]);
	
	//parameter checks
	if (myid >= N)
	{
		printf ("wrong id\n");
		return 1;
	}	

	if (nodes != N)
	{
		printf ("wrong number of nodes\n");
		return 1;
	}	
	
	//get info on machines from the file using fopen and fscanf and populate the array of machines-struct
	//******STUDENT WORK******
	if ((fp = fopen(argv[3], "r")) == NULL){
		printf("Unable to open file 4\n");
		return 0;
	}

	for (i = 0; i < N; i++){
		fscanf(fp, "%s %s %d", machines[i].name, machines[i].ip, &machines[i].port);
	}
	fclose(fp);

	// get costs from the costs file and populate the matrix
	if ((fp = fopen (argv[4], "r")) == NULL)
	{
		//******STUDENT WORK******
		printf("Unable to open file\n");
		return 0;
	}

	//******STUDENT WORK******
	for (i = 0; i < N; i++){
		for (j = 0; j < N; j++){
			fscanf(fp, "%d", &costs[i][j]);
		}
	}
	fclose(fp);	
    // init address
    //******STUDENT WORK******
	addr.sin_family = AF_INET;
	addr.sin_port = htons(machines[myid].port);
	addr.sin_addr.s_addr = INADDR_ANY;

    // create socket
    //******STUDENT WORK******
	if ((sock = socket(AF_INET, SOCK_DGRAM, 0))==0){
		perror("Socket failed");
		exit(1);
	}

    // bind
    //******STUDENT WORK******
	if ((bind(sock, (struct sockaddr *)&addr, sizeof(struct sockaddr))) < 0){
		perror("Failiure binding address to the socket");
		exit(1);
	}
	// create threads and initiate mutex
	pthread_mutex_init (&lock, NULL);
	pthread_create (&thr1, NULL, receive_info, NULL);
	pthread_create (&thr2, NULL, run_link_state, NULL);

	// read changes from the keyboard, update the costs matrix inform other nodes about the changes
	{ // This section can be inside the main or can be a thread by itself
		int tempid, tempcost, new[3];
		struct hostent *temphost;
		for (i = 0; i < 3; i++)
		{
			//Get the id and costs from the user
			printf("NeighborsID\n");
			scanf("%d", &tempid);
			printf("Cost change\n");
			scanf("%d", &tempcost);
			
			//update acosts array values
			pthread_mutex_lock(&lock);
			costs[myid][tempid] = tempcost;
			costs[tempid][myid] = tempcost;
			pthread_mutex_unlock(&lock);
			
			for (j = 0; j < N; j++){
				if (j != myid){
					//set up the socket to send
					temphost = (struct hostent *)gethostbyname(machines[j].name);
					otheraddr.sin_family = AF_INET;
					otheraddr.sin_port = htons(machines[j].port);
					inet_pton(AF_INET, machines[j].ip, &otheraddr.sin_addr.s_addr);
					
					//assign the values and send them to the other machine
					new[0] = myid;
					new[1] = tempid;
					new[2] = tempcost;
					printf("Updating machine %d: %d\n", j, tempcost);
					sendto(sock, new, sizeof(new), 0, (struct sockaddr *)&otheraddr, addrlen);
				}
			}
			
			printf ("sent\n");
		}
	}	

}


/**********************
 * receive info
 **********************/
//If there is a cost update on other machine, they will let us know through a UDP packet. We need to receive that packet and update our costs table
void *receive_info (void *arg)
{
	int	new[3];
	int	nbytes;
	int	n0, n1, n2;
	socklen_t slength = sizeof(addr);

	while(1){
		//waits to receive a cost change and unpacks it.
		recvfrom(sock, new, sizeof(new), 0, (struct sockaddr *)&addr, &slength);
		n0 = new[0];
		n1 = new[1];
		n2 = new[2];

		//reassigns costs array
		pthread_mutex_lock(&lock);
		costs[n0][n1] = n2;
		costs[n1][n0] = n2;
		pthread_mutex_unlock(&lock);

		printf("Costs updated\n");
		print_costs();
	}
}


/**********************
 * run_link_state
 **********************/
// This thread runs the Dijkastra's algorithm on the cost table and calculates thte shortest path
void *
run_link_state (void *arg)
{
	int	taken[N];
	int	min, spot;
	int	i, j;
	int	r;
	int count;

	//******STUDENT WORK******
	while(1){
		//loops through each row in the table to a djkikstra
		printf ("new-shortest distances:\n");
		for (i = 0; i < N; i++){
			//initializes the least costs distance array and the taken array which is used to keep track of which cells have been visited.
			for (j = 0; j < N; j++){
				distances[j] = costs[i][j];
				taken[j] = 0;
			}
			
			count = 0;
			while (count < N){
				min = 101;
				spot = -1;
				
				//finds the minimum value
				for (j = 0; j < N; j++){
					if (distances[j] < min && taken[j] == 0){
						min = distances[j];
						spot = j;
					}
				}
				
				//runs djikstra's algorithn to find the shortest distance to all nodes
				taken[spot] = 1;
				for (j = 0; j < N; j++){
					if (taken[j] == 0)
						if (distances[spot] + costs[spot][j] < distances[j])
							distances[j] = distances[spot] + costs[spot][j];
					
				}
				count++;
			}
			for (j = 0; j < N; j++)
				printf ("%d ", distances[j]);
			printf ("\n");
		}		
		sleep(15);
	}
}


/**********************
 * print costs
 **********************/
void
print_costs (void)
{
	int i, j;

	for (i = 0; i < N; i++)
	{
		for (j = 0; j < N; j++)
		{
			pthread_mutex_lock (&lock);
			printf ("%d ", costs[i][j]);
			pthread_mutex_unlock (&lock);
		}
		printf ("\n");
	}

}
