#include <stdint.h>
#include <vector>
#include <random>
#include <string>
#include <bitset>
#include <cmath>
#include "../../headers/cube/handle-cube-input.hpp"
#include "../../headers/manhattan-hashing.hpp"

using namespace std;
#include <iostream>

string distribute_Bits() {
	random_device generator;
	uniform_real_distribution<float> distribution (0.0, 2.0);

	// Generate a new int number
	int result = static_cast<int>(distribution(generator));
	string s = bitset<1>(result).to_string(); // string conversion

	return s;
}

string calculateCubeG_X(int d_space, int image, int file_type) {
	int h_x;
	string bit;
	string cubeG_X;
	// why resize every time?
	for (int i=0; i<d_space; i++) {
		h_x = createH_X(d_space, image, file_type);
		// check if h_x exists in current f
		// ??is correct? TESTING NEEDED
		if (projections[i].find(h_x) == projections[i].end()) {
			bit = distribute_Bits();
			// it does not exists, so add it
			projections[i][h_x] = bit;
			cout << "projectionssssssss: " << projections[i][h_x] << endl;
		}
		// now that we have f_i(h_i(p)) as a bit
		// append it in bitstring
		cubeG_X.append(projections[i][h_x]);
	}
	return cubeG_X;
}

// find pos, correct bucket to put my image
void insertToHypercube () {

}

int calculateLogDspace(int d) {
	return (int)(log(d) - 1);
}