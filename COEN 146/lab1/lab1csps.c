//Austin Johnson
//COEN 146
//Lab1


#include <math.h>
#include <stdio.h>

//recursively finds the factorial
double factorial(double n){
	if (n <= 1)
		return 1;
	return n*factorial(n-1);
}

//find the binomial coefficient
double coefficient(int n, int num){
	return factorial(n)/(factorial(num)*factorial(n-num));
}


int main(int argc, int *argv[]){
	//declarizations
	int linkBandwidth, userBandwidth, nCSusers, nPSusers;
	double tPSuser, pPSusers, pPSusersNotBusy;
	
	//default values given in the lab
	linkBandwidth = 200 * pow(10, 6);
	userBandwidth = 20 * pow(10,6);
	tPSuser = .1;
	nPSusers = 19;
	
	//Finding calculated values	
	nCSusers = linkBandwidth / userBandwidth;
	pPSusers = tPSuser;
	pPSusersNotBusy = 1 - pPSusers;
	
	//Printing values asked for in the lab
	printf("Step 6:\na. %d\n",nCSusers);
	printf("Step 7:\na. pSusers: %f\n", tPSuser);
	printf("b. pPSusersNotBusy: %f\n",pPSusersNotBusy);
	printf("c. All other users are not busy: %f\n", pow(1-pPSusers, nPSusers-1));
	printf("d. One specific user is transmitting the rest are not: %f\n",pPSusers*pow(pPSusersNotBusy, nPSusers-1));
	printf("e. The probability one user is busy: %f\n",nPSusers*(pPSusers*pow(pPSusersNotBusy,nPSusers-1)));
	printf("f. 10 specific users are busy and the rest are idle: %f\n",pow(pPSusers, 10)*pow(pPSusersNotBusy,nPSusers-10));
	printf("g. Any 10 users are busy and the others are idle: %f\n",coefficient(nPSusers, 10)*pow(pPSusers, 10)*pow(pPSusersNotBusy,nPSusers-10));
	
	//sums the value found in 7h
	int i=11, sum=0;
	while(i <= nPSusers){
		sum += coefficient(nPSusers, i)*pow(pPSusers, i)*pow(pPSusersNotBusy, nPSusers-i);
		i++;
	}

	printf("h. More than 10 users are transmiitng and the others are idle: %f\n", sum);
}
