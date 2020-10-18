#include <stdint.h>
#include <vector>
#include <random>
#include <string>
#include <bitset>
#include <cmath>
#include <unordered_map>
#include "../../headers/manhattan-hashing.hpp"
#include "../../headers/search.hpp"
#include "../../headers/distances.hpp"
#include "../../headers/modulo.hpp"
// #include "../../headers/cube/projection.hpp"

using namespace std;

// it takes h_i(p) and bitstring (bucket in Hypercube)
vector<unordered_map<int, string> > projections;

string distribute_Bits() {
	random_device generator;
	uniform_real_distribution<float> distribution (0.0, 2.0);

	// Generate a new int number
	int result = static_cast<int>(distribution(generator));
	string s = bitset< 64 >(result).to_string(); // string conversion

	return s;
}

string calculateCubeG_X(int d_space, int image, int file_type) {
	int h_x;
	string bit;
	string cubeG_X;
	// string
	// why resize every time?
	projections.resize(d_space);
	for (int i=0; i<d_space; i++) {
		h_x = createH_X(d_space, image, file_type);
		// check if h_x exists in current f
		// ??is correct? TESTING NEEDED
		if (projections[i].find(h_x) == projections[i].end()) {
			bit = distribute_Bits();
			// it does not exists, so add it
			projections[i][h_x] = bit; 
		}
		else {
			bit = projections[i][h_x];
		}
		// now that we have f_i(h_i(p)) as a bit
		// append it in bitstring
		cubeG_X.append(bit);
	}
	return cubeG_X;
}

// find pos, correct bucket to put my image
void insertToHypercube () {

}

int calculateLogDspace(int d) {
	return (log10(d) - 3);
}