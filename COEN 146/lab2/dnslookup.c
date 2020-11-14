#include <stdio.h>

#define RTT0 3
#define RTT1 20
#define RTT2 26
#define RTTHTTP 47
#define objects 6
#define n 5

int main(int argc, char *argv[]){
	int totalRTTDNS = RTT0 + RTT1 + RTT2;
	printf("Total time elapsed: %d\n", totalRTTDNS + 2*RTTHTTP);
	printf("b. %d\n", totalRTTDNS + 2*(objects+1)*RTTHTTP);

	int loops;
	loops = (objects / n)+1;
	if (objects%n == 0)
		loops --;
	int persistent = totalRTTDNS + (loops+1)*RTTHTTP;
	int npersistent = totalRTTDNS + 2*(loops)*RTTHTTP; 

	printf("C. persistent: %d\n", persistent);
	printf("non-persisent: %d\n", npersistent);	
}
