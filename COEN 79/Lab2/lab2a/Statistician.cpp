#include <iostream>
#include <cassert>
#include "statistician.h"

using namespace std;
using namespace coen79_lab2;

namespace coen79_lab2 {

	//sets all parameters to their coresponding value
	statistician::statistician (double initial_tSum, double initial_min, double initial_max, int initial_tLength) {
		tSum = initial_tSum;
		min = initial_min;
		max = initial_max;
		tLength = initial_tLength;
	}

	//adds sum and length together. finds the minimum and maximum of the superset of s1 and s2. returns the new set
	statistician operator +(statistician& s1, statistician& s2) {
		int nlength = s1.length() + s2.length();
		double min, max, sum;
		sum = s2.sum() + s1.sum();

		if (s2.maximum() >= s1.maximum())
			max = s2.maximum();
		else
			max = s1.maximum();

		if (s2.minimum() >= s1.minimum())
			min = s1.minimum();
		else
			min = s2.minimum();
		statistician stat(sum, min, max, nlength);
		return stat;
	}

	//multiplies every val of statistsician aside from the length and the statistician
	statistician operator *(double scale, statistician& s) {
		double temp;

		double nSum = s.sum() * scale;
		double nMin = s.minimum() * scale;
		double nMax = s.maximum() * scale;
		if (scale < 0) {
			temp = nMin;
			nMin = nMax;
			nMax = temp;
		}
		statistician stat(nSum,nMin,nMax,s.length());

		return stat;
	}

	//checks if every val is the same and returns
	bool operator ==(statistician& s1, statistician& s2) {
		return (s2.sum() == s1.sum()) && (s2.length() == s1.length()) && (s2.minimum() == s1.minimum()) && (s2.maximum() == s1.maximum());
	}

	//updates sum and length. checks if it is the new min or max. sets it to min or max if the length is 0
	void statistician::next(double uInput) {
		tSum += uInput;
		if ((uInput < min) || (tLength == 0))
			min = uInput;
		if ((uInput > max) || (tLength == 0))
			max = uInput;
		tLength++;
		return;
	}

	//returns length
	int statistician::length() {
		return tLength;
	}

	//returns sum
	double statistician::sum() {
		return tSum;
	}

	//uses formula for mean to return mean
	//precondition: length > 0
	double statistician::mean() {
		assert(tLength != 0);
		return (tSum / tLength);
	}

	//return min
	//precondition: length > 0
	double statistician::minimum() {
		assert(tLength != 0);
		return min;
	}

	//return max
	//precondition: length > 0
	double statistician::maximum() {
		assert(tLength != 0);
		return max;
	}

	//sets all values to 0 to reset the class to its default state
	void statistician::reset() {
		tSum = 0;
		tLength = 0;
		min = 0;
		max = 0;
	}
}