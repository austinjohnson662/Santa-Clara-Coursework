#include "random.h"

using namespace std;
using namespace coen79_lab2;

namespace coen79_lab2 {
	rand_gen::rand_gen(int init_seed, int init_multiplier, int init_increment, int init_modulus) {
		seed = init_seed;
		multiplier = init_multiplier;
		increment = init_increment;
		modulus = init_modulus;
	}

	int rand_gen::next() {
		int next_seed = (multiplier * seed + increment) % modulus;
		seed = next_seed;
		return seed;
	}

	void rand_gen::set_seed(int new_seed) {
		seed = new_seed;
	}
}