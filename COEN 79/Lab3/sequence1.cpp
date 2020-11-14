#include "sequence1.h"
#include <cassert>
#include <math.h>

using namespace coen79_lab3;
using namespace std;

namespace coen79_lab3 {

	//constructor
	sequence::sequence() {
		array = new value_type[CAPACITY];
		index = 0;
		length = 0;
	}

	//Modification member functions
	void sequence::start() {
		index = 0;
	}

	void sequence::end() {
		index = length - 1;
		if (length == 0)
			index++;
	}

	void sequence::last() {
		index = CAPACITY - 1;
	}

	void sequence::advance() {
		assert(is_item());
		if (index != CAPACITY - 1)
			index++;
	}

	void sequence::retreat() {
		if (index != 0)
			index--;
	}

	//if 0 items inserts into the first element
	//if there are multiple elements the function shifts all items to right starting at the index. then inserts into the vacated spot
	//cursor set to new item
	void sequence::insert(const value_type& entry) {
		assert(size() < CAPACITY);
		if (length == 0) {
			array[0] = entry;
			index = 0;
			length++;
			return;
		}
		int i;
		for (i = length; i >= index+1; --i) {
			array[i] = array[i-1];
		}
		array[i] = entry;
		length++;
	}

	//shifts all items after the cursor another spot to make room for the new item after the cursor
	//cursor set to new item
	void sequence::attach(const value_type& entry) {
		assert(size() < CAPACITY);
		if (length == 0) {
			array[length] = entry;
			index = length++;
			return;
		}
		int i;
		for (i = length; i > index+1; --i) {
			array[i] = array[i - 1];
		}
		array[++index] = entry;
		length++;
		return;
	}

	//removes the item then shifts all the elements back to fill the open spot
	void sequence::remove_current() {
		assert(is_item());
		int i;
		for (i = index+1; i < length; i++) {
			array[i-1] = array[i];
		}
		length--;
		return;
	}

	//uses insert function by setting the cursor to 0 and shifting
	void sequence::insert_front(const value_type& entry) {
		assert(size() < CAPACITY);
		index = 0;
		insert(entry);
		return;
	}

	//simply inserts the new item at the back of the array
	void sequence::attach_back(const value_type& entry) {
		assert(size() < CAPACITY);
		array[length] = entry;
		length++;
		index = length - 1;
		return;
	}

	//removes the first item then shifts all items to fill the hole
	void sequence::remove_front() {
		assert(is_item());
		int i;
		for (i = length - 1; i > 0; i--) {
			array[i - 1] = array[i];
		}
		length--;
		index = 0;
		return;
	}

	sequence::size_type sequence::size() const{
		return length;
	}

	//iff there are items in the array it will return true
	bool sequence::is_item() const {
		if (index < length)
			return true;
		return false;
	}

	sequence::value_type sequence::current() const {
		assert(is_item());
		return array[index];
	}

	sequence::value_type sequence::operator [](int get) const {
		assert(get < length);
		return array[get];
	}

	//sum/length
	double sequence::mean() const {
		int i;
		double sum = 0;
		for (i = 0; i < length; i++) {
			sum += array[i];
		}
		return sum / length;
	}

	//sqrt((summation(xi-mean)^2)/N)
	double sequence::standardDeviation() const {
		int i;
		double average = mean(), stdTop = 0;
		for (i = 0; i < length; i++) {
			stdTop += (array[i] - average)*(array[i] - average);
		}
		return sqrt(stdTop / length);
	}

	//loops through the array and attatches each one into the new array and return the new array.
	sequence operator +(const sequence& lhs, const sequence& rhs) {
		assert((lhs.size() + rhs.size()) < sequence::CAPACITY);
		
		int i;
		sequence s;
		for (i = 0; i < lhs.size(); i++)
			s.attach(lhs[i]);
		for (i = 0; i < rhs.size(); i++)
			s.attach(rhs[i]);
		return s;
	}

	//loops through the array and attatches each one into the new array and return the new array.
	sequence operator +=(sequence& lhs, sequence& rhs) {
		assert((lhs.size() + rhs.size()) < sequence::CAPACITY);

		int i;
		sequence s;
		for (i = 0; i < lhs.size(); i++)
			s.attach(lhs[i]);
		for (i = 0; i < rhs.size(); i++)
			s.attach(rhs[i]);
		return s;
	}

	sequence::value_type summation(const sequence &s) {
		sequence::value_type sum = 0;
		int i;
		for (i = 0; i < s.size(); i++) {
			sum += s[i];
		}
		return sum;
	}
}