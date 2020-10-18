#include <stdint.h>
#include <vector>
#include <random>
#include <unordered_map>
#include "../../headers/manhattan-hashing.hpp"
#include "../../headers/search.hpp"
#include "../../headers/distances.hpp"
#include "../../headers/modulo.hpp"

using namespace std;

vector<unordered_map<int, int> > projections;

int distribute_Bits() {
	random_device generator;
	uniform_real_distribution<float> distribution (0.0, 2.0);

	// Generate a new double number
	return static_cast<int>(distribution(generator));
}

void calculateF_Dcomponents(int d_space, int d, int image, int file_type) {
	int h_x;
	int bit;
	projections.resize(d_space);
	for (int i=0; i<d_space; i++) {
		h_x = createH_X(d, image, file_type);
		// check if h_x exists in current f
		if (projections[i].find(h_x) == projections[i].end()) {
			// it does not exists, so add it
			bit = distribute_Bits();
			projections[i][h_x] = bit;
		}
	}
}