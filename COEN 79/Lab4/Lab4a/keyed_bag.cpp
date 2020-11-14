#include <cstdlib>
#include <string>
#include <cassert>
#include <iostream>
#include "keyed_bag.h"

using namespace std;
using namespace coen79_lab4;

namespace coen79_lab4 {
	keyed_bag::keyed_bag(){
		int i;
		for (i = 0; i < CAPACITY; i++) {
			keys[i] = '\0';
			data[i] = NULL;
		}
		itemcount = 0;
	}

	void keyed_bag::erase() {
		int i;
		for (i = 0; i < itemcount; i++) {
			keys[i] = '\0';
			data[i] = NULL;
		}
		itemcount = 0;
	}

	//loops through the array until it reaches the end or reaches an item with the given key
	//removes the item and shifts the array if the key is present and returns true. Otherwise just returns false;
	bool keyed_bag::erase(const key_type& key) {
		assert(size() < CAPACITY);
		int i=0, j;
		while ((i < CAPACITY) && (keys[i] != key))
			i++;
		if (keys[i] == key) {
			for (j = i + 1; j < itemcount; j++) {
				keys[j - 1] = keys[j];
				data[j - 1] = data[j];
			}
			itemcount--;
			return true;
		}
		else {
			return false;
		}
	}

	//checks for size then inserts at the end of the arrays
	void keyed_bag::insert(const value_type& entry, const key_type& key) {
		assert(size() < CAPACITY);
		assert(!has_key(key));
		keys[itemcount] = key;
		data[itemcount] = entry;
		itemcount++;
		return;
	}

	//loops through keys. if it is not a duplicate key it adds both the items to the end of the array
	void keyed_bag::operator +=(const keyed_bag& addend) {
		assert(itemcount + addend.itemcount <= CAPACITY);
		int i;
		for (i = 0; i < addend.itemcount; i++) {
			if (!has_key(addend.keys[i])) {
				keys[itemcount] = addend.keys[i];
				data[itemcount] = addend.data[i];
				itemcount++;
			}
		}
	}

	//lops through the array checking if any of the keys match key
	bool keyed_bag::has_key(const key_type& key) const{
		int i;
		for (i = 0; i < itemcount; i++) {
			if (keys[i] == key)
				return true;
		}
		return false;
	}

	//returns the data for the matching key
	keyed_bag::value_type keyed_bag::get(const key_type& key) const{
		assert(has_key(key));
		int i;
		for (i = 0; i < itemcount; i++) {
			if (keys[i] == key)
				return data[i];
		}
		return NULL;
	}

	keyed_bag::size_type keyed_bag::count(const value_type& target) const {
		int count=0,i;
		for (i = 0; i < itemcount; i++) {
			if (data[i] == target)
				count++;
		}
		return count;
	}

	//returns count
	keyed_bag::size_type keyed_bag::size() const{
		return itemcount;
	}

	//uses the has key function to check if there is any overlapping keys
	bool keyed_bag::hasDuplicateKey(const keyed_bag& otherBag) const{
		int i;
		for (i = 0; i < itemcount; i++) {
			if (has_key(otherBag.keys[i]))
				return true;
		}
		return false;
	}

	//returns a temporary keyed_bag which uses += to add b1 b2. returns temp.
	keyed_bag operator +(const keyed_bag& b1, const keyed_bag& b2) {
		assert(b1.itemcount + b2.itemcount < keyed_bag::CAPACITY);
		keyed_bag temp;
		temp += b1;
		temp += b2;
		return temp;
	}
}