#include <iostream>
#include <cassert>
#include <cmath>
#include <climits>
#include <iomanip>
#include "poly.h"

using namespace std;
using namespace coen79_lab4;

namespace coen79_lab4 {
	//ascends the array. the highest non-zero value's index replaces degree
	void polynomial::update_current_degree() {
		int i, high = 0;
		for (i = 0; i < CAPACITY; i++) {
			if (data[i] != 0)
				high = i;
		}
		high_degree = high;
	}

	//sets all values to zero. the adds the parameter to the array
	polynomial::polynomial(double c, unsigned int exponent) {
		int i;
		for (i = 0; i < CAPACITY; i++)
			this->data[i] = 0;
		this->high_degree = 0;
		this->data[exponent] = c;
		this->update_current_degree();
	}

	//sets data[exponent] to coefficient
	void polynomial::assign_coef(double coefficient, unsigned int exponent){
		assert(exponent <= MAXIMUM_DEGREE);
		data[exponent] = coefficient;
		update_current_degree();
	}

	//increments data[exponent] by amount
	void polynomial::add_to_coef(double amount, unsigned int exponent) {
		assert(exponent <= MAXIMUM_DEGREE);
		data[exponent] += amount;
		update_current_degree();
	}

	//sets all coefficients to zero
	void polynomial::clear() {
		int i;
		for (i = 0; i < CAPACITY; i++) {
			data[i] = 0;
		}
		update_current_degree();
	}

	polynomial polynomial::antiderivative() const {
		assert(degree() < MAXIMUM_DEGREE);
		polynomial temp(0.0, 0);
		int i;
		for (i = 0; i < CAPACITY - 1; i++) {
			temp.data[i + 1] = data[i]/(i+1);
		}
		temp.data[0] = 0;
		temp.update_current_degree();
		return temp;
	}

	double polynomial::coefficient(unsigned int exponent) const {
		return data[exponent];
	}

	double polynomial::definite_integral(double x0, double x1) const {
		polynomial p = antiderivative();
		return p.eval(x1) - p.eval(x0);
	}

	unsigned int polynomial::degree() const {
		return high_degree;
	}

	polynomial polynomial::derivative() const {
		int i;
		polynomial p;
		for (i = 0; i < CAPACITY-1; i++) {
			p.data[i] = data[i + 1]*(i+1);
		}
		p.update_current_degree();
		return p;
	}

	double polynomial::eval(double x) const{
		int sum = 0, i;
		for (i = 0; i < CAPACITY; i++) {
			sum += pow(x, i) * data[i];
		}
		return sum;
	}

	bool polynomial::is_zero() const {
		int i;
		for (i = 0; i < CAPACITY; i++) {
			if (data[i] != 0)
				return false;
		}
		return true;
	}

	unsigned int polynomial::next_term(unsigned int e) const {
		int i;
		for (i = e + 1; i < CAPACITY; i++) {
			if (data[i] != 0)
				return i;
		}
		return 0;
	}

	unsigned int polynomial::previous_term(unsigned int e) const {
		int i;
		for (i = e - 1; i >= 0; i--) {
			if (data[i] != 0)
				return i;
		}
		return UINT_MAX;
	}

	double polynomial::operator()(double x) const {
		return eval(x);
	}

	polynomial operator +(const polynomial& p1, const polynomial& p2) {
		polynomial temp;
		int i;
		for (i = 0; i < polynomial::CAPACITY; i++) {
			temp.add_to_coef(p1.coefficient(i) + p2.coefficient(i), i);
		}
		temp.update_current_degree();
		return temp;
	}

	polynomial operator -(const polynomial& p1, const polynomial& p2) {
		polynomial temp;
		int i;
		for (i = 0; i < polynomial::CAPACITY; i++) {
			temp.add_to_coef(p1.coefficient(i) - p2.coefficient(i), i);
		}
		temp.update_current_degree();
		return temp;
	}

	polynomial operator *(const polynomial& p1, const polynomial& p2) {
		assert(p1.degree() + p2.degree() <= polynomial::MAXIMUM_DEGREE);
		polynomial p3;
		int i, j;
		for (i = 0; i <= p1.degree(); i++) {
			for (j = 0; j <= p2.degree(); j++) {
				p3.add_to_coef(p1.coefficient(i) + p2.coefficient(j), i + j);
			}
		}
		p3.update_current_degree();
		return p3;
	}

	std::ostream& operator << (std::ostream& out, const polynomial& p) {
		unsigned int i = p.degree();
		streamsize s = out.precision();
		out << fixed;
		out << setprecision(1);
		for (int i = p.degree(); i >= 0; i--) {
			if (p.degree() == 0) {
				cout << p.coefficient(i);
			}
			else if (p.coefficient(i)!= 0){
				if (i == p.degree()) {
					if (i > 1)
						out << p.coefficient(i) << "X^" << i << ' ';
					else if (i == 1)
						out << p.coefficient(i) << "X ";
					else if (i == 0)
						out << p.coefficient(i) << " ";

				}
				else if (i < p.degree() && i > 1) {
					if (p.coefficient(i) < 0)
						out << "- " << p.coefficient(i)*-1;
					else
						out << "+ " << p.coefficient(i);
					out << "X^" << i << " ";
				}
				else if (i == 1) {
					if (p.coefficient(i) < 0)
						out << "- " << p.coefficient(i) * -1;
					else
						out << "+ " << p.coefficient(i);
					out << "X ";
				}
				else if (i == 0) {
					if (p.coefficient(i) < 0)
						out << "- " << p.coefficient(i) * -1;
					else
						out << "+ " << p.coefficient(i);
				}
			}
		}
		out.unsetf(ios_base::floatfield);
		out << setprecision(s);
		return out;
	}
}