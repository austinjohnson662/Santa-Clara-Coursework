#ifndef STATS_H
#define STATS_H

#include <iostream>

using namespace std;

namespace coen79_lab2 {
	class statistician {
	private:
		double tSum;
		double min;
		double max;
		int tLength;
	public:
		statistician(double initial_tSum = 0.0, double initial_min = 0.0, double initial_max = 0.0, int initial_tLength = 0);
		//Postcondition: sets all of the classes varibles to the parameters given. If no parameters are given 0 is assigned to all of them.

		void next(double uInput);
		//postcondition: updates all the values in the data set

		int length();
		//postcondition: returns the how many elements are in the data set

		double sum();
		//postcondition returns the sum of the data set

		double mean();
		//precondition: length must be greater than 0
		//postcondition returns the mean of th data set

		double minimum();
		//precondition: length must be greater than 0
		//postcondition returns the minimum of the data set

		double maximum();
		//precondition: length must be greater than 0
		//postcondition returns the maximum of the data set

		void reset();
		//postcondition sets all the values to zero
	};
	statistician operator +(statistician& s1, statistician& s2);
	//Postcondition: The statistician that is returned contains all the numbers of the sequences of s1 and s2.

	statistician operator *(double scale, statistician& s);
	//Postcondition: The statistician that is returned contains the same numbers that s does, but each number has been multiplied by the scale number.
	
	bool operator ==(statistician& s1, statistician& s2);
	//Postcondition: The return value is true if s1 and s2 have the zero length. Also, if the length is greater than zero,
	//then s1 and s2 must have the same length, the same  mean, the same minimum, the same maximum, and the same sum.
}

#endif