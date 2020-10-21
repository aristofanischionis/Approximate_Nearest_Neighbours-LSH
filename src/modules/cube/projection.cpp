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

int distribute_Bits() {
	random_device generator;
	uniform_real_distribution<float> distribution (0.0, 2.0);
	// Generate a new int number
	int result = static_cast<int>(distribution(generator));
	return result;
}

// Calculate h(x) using the formula from the theory
int create_CubeH_X(uint64_t d, int image, int file_type) {
	// then calculate hx
	int hx = file_type == INPUT_FILE ? \
		calculateH_XComponent(d, all_cube_images[image]) : \
		calculateH_XComponent(d, query_cube_images[image]);
    return hx;
}

string decimalToBinary(int n) { 
    //finding the binary form of the number and  
    //converting it to string.  
    string s = bitset<32> (n).to_string();
    //Finding the first occurance of "1" 
    //to strip off the leading zeroes. 
    const auto loc1 = s.find('1');

    if(loc1 != string::npos)
    	return s.substr(loc1);
    
    return "0";
} 

string calculateCubeG_X(int d, int image, int file_type) {
	int h_x;
	int bit;
	int shift = 1;
	int cubeG_X = 0;
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
		if (i == 0) {
			// if bit is set
			// then just shift
			cubeG_X = projections[i][h_x];
		}
		else{
			cubeG_X <<= shift;
			cubeG_X |= projections[i][h_x];
		}
	}
	return decimalToBinary(cubeG_X);
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
	Hypercube.insert(make_pair(g_x, image));
}

// print Hypercube
void printHypercube() {
	multimap <string, int> :: iterator itr;
	for (itr = Hypercube.begin(); itr != Hypercube.end(); ++itr)
        cout<< itr->first<<'\t'<< itr->second << endl;
}

int calculateLogDspace(int d) {
	return (int)(log2(d) - 1);
}

int hammingDistance(string queryHash, string bucketHash) {
	int i = 0, distance = 0;
	while(queryHash[i] != '\0') {
		if(queryHash[i] != bucketHash[i]) {
			distance++;
		}
		i++;
	}
	return distance;
}

vector<int> findImagesInBucket(string hash) {
	vector<int> result;
	auto search = Hypercube.equal_range(hash);
	for (auto i = search.first ; i != search.second ; ++i) {
		result.push_back(i->second);
	}
	return result;
}

// find strings that have hamming distance dist
vector<string> findHashWithSpecificHammingDist(string queryHash, int dist, int maximumProbes) {
	vector<string> res;
	multimap <string, int> :: iterator itr;
	int localProbes = maximumProbes;
	for (itr = Hypercube.begin(); itr != Hypercube.end(); ++itr)
	{
		if(hammingDistance(queryHash, itr->first) == dist) {
			// if doesn't exist in vector, i push back
			if(find(res.begin(), res.end(), itr->first) == res.end()){
				res.push_back(itr->first);
				localProbes--;
			}
			if(localProbes == 0) break;
		}
	}
	return res;
}

vector<int> findAllNeighboursToBeChecked(string queryHash, int maximumN, int probes) {
	int currentHamming = 0;
	int numberOfProbesToCheck = probes;
	vector<string> currentNeighbourBuckets;
	vector<int> currentPossibleNeighbours;
	vector<int> allPossibleNeighbours;
	do
	{
		currentNeighbourBuckets = findHashWithSpecificHammingDist(queryHash, currentHamming, numberOfProbesToCheck);
		for (int buck = 0; buck < currentNeighbourBuckets.size(); buck++) {

			currentPossibleNeighbours = findImagesInBucket(currentNeighbourBuckets[buck]);
			// checked some more
			numberOfProbesToCheck--;
			// well now push back elements to allPossibleNeighbours
			for (int el = 0; el < currentPossibleNeighbours.size(); el++){
				allPossibleNeighbours.push_back(currentPossibleNeighbours[el]);
				if(allPossibleNeighbours.size() == maximumN) break;
			}

			if (numberOfProbesToCheck == 0) break;
			currentPossibleNeighbours.clear();
		}
		currentNeighbourBuckets.clear();
		currentHamming++;
	} while (true);

	return allPossibleNeighbours;
}

// TODO:
// If manhattan q, image < radius and allNeighbours are less or equal to N
// then print to file
void hypercubeANN(int q_num, int probes, int N, int points_M, int radius, int d) {
	
	string queryHash = calculateCubeG_X(d, q_num, QUERY_FILE);
	vector<int> allPossibleNeighbours;
	allPossibleNeighbours = findAllNeighboursToBeChecked(queryHash, points_M, probes);

	allPossibleNeighbours.clear();
}