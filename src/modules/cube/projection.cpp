#include <stdint.h>
#include <vector>
#include <random>
#include <string>
#include <bitset>
#include <cmath>
#include "../../headers/cube/handle-cube-input.hpp"
#include "../../headers/manhattan-hashing.hpp"
#include "../../headers/common.hpp"

using namespace std;
#include <iostream>

string distribute_Bits() {
	random_device generator;
	uniform_real_distribution<float> distribution (0.0, 2.0);

	// Generate a new int number
	int result = static_cast<int>(distribution(generator));
	
	return bitset<1>(result).to_string();
}

// Calculate h(x) using the formula from the theory
int create_CubeH_X(uint64_t d, int image, int file_type) {
	// then calculate hx
	int hx = file_type == INPUT_FILE ? \
		calculateH_XComponent(d, all_cube_images[image]) : \
		calculateH_XComponent(d, query_cube_images[image]);
    return hx;
}

string calculateCubeG_X(int d, int image, int file_type) {
	int h_x;
	string bit;
	string cubeG_X;
	// why resize every time?
	for (int i=0; i<d_space; i++) {
		h_x = create_CubeH_X(d, image, file_type);
		// check if h_x exists in current f
		if (projections[i].find(h_x) == projections[i].end()) {
			bit = distribute_Bits();
			// it does not exists, so add it
			projections[i][h_x] = bit;
		}
		// now that we have f_i(h_i(p)) as a bit
		// append it in bitstring
		cubeG_X.append(projections[i][h_x]);
	}
	return cubeG_X;
}

// print array of f(d')
void printF_X() {
	for (unsigned int i=0; i<projections.size(); i++) {
		for (auto& it: projections[i]) {
			cout<<it.first<<"	"<<it.second<<endl;
		}
	}
}

// find pos, correct bucket to put my image
void insertToHypercube(string g_x, int image) {
	Hypercube.insert({g_x, image});
}

// print Hypercube
void printHypercube() {
	multimap <string, int> :: iterator itr;
	for (itr = Hypercube.begin(); itr != Hypercube.end(); ++itr) {
        cout<< itr->first<<'\t'<< itr->second << endl;
    } 
}

int calculateLogDspace(int d) {
	return (int)(log2(d) - 1);
}