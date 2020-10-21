#include <stdint.h>
#include <vector>
#include <random>
#include <bitset>
#include <cmath>
#include <chrono>
#include <fstream>
#include <algorithm>
#include "../../headers/cube/handle-cube-input.hpp"
#include "../../headers/manhattan-hashing.hpp"
#include "../../headers/common.hpp"
#include "../../headers/distances.hpp"

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

// function to all values of duplicate keys in a multimap
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
	for (itr = Hypercube.begin(); itr != Hypercube.end(); ++itr) {
		if(hammingDistance(queryHash, itr->first) == dist) {
			// if it doesn't exist in vector, push it back
			if(find(res.begin(), res.end(), itr->first) == res.end()) {
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

	do {
		currentNeighbourBuckets = findHashWithSpecificHammingDist(queryHash, currentHamming, numberOfProbesToCheck);
		for (unsigned int buck = 0; buck < currentNeighbourBuckets.size(); buck++) {

			currentPossibleNeighbours = findImagesInBucket(currentNeighbourBuckets[buck]);
			// checked some more
			numberOfProbesToCheck--;
			// now push back elements to allPossibleNeighbours
			for (unsigned int el = 0; el < currentPossibleNeighbours.size(); el++) {
				allPossibleNeighbours.push_back(currentPossibleNeighbours[el]);
				if(allPossibleNeighbours.size() == (unsigned int)maximumN) break;
			}

			if (numberOfProbesToCheck == 0) break;
			currentPossibleNeighbours.clear();
		}
		currentNeighbourBuckets.clear();
		currentHamming++;
	} while (true);

	return allPossibleNeighbours;
}

// Brute Force
vector<pair <unsigned int, unsigned int> > hypercube_Full_Search(int d, int n, uint32_t q_num, int number_of_images) {
    vector<pair <unsigned int, unsigned int> > n_neighbours;
    vector<pair <unsigned int, unsigned int> >::iterator it;
    unsigned int current_distance = 0;
    int* qarray, *parray;

    // loop over the images array
    for (int i=0; i<number_of_images; i++) {
        qarray = convertArray(query_cube_images[q_num], d);
        parray = convertArray(all_cube_images[i], d);
        current_distance = manhattanDistance(qarray, parray, d);
        delete[] qarray;
        delete[] parray; 
        n_neighbours.push_back(make_pair(i, current_distance));
    }
    sort(n_neighbours.begin(), n_neighbours.end(), [](const pair<unsigned int, unsigned int> &left, const pair<unsigned int, unsigned int> &right) {
        return left.second < right.second;
    });
    if (n_neighbours.size() >  static_cast<unsigned int>(n)) n_neighbours.resize(n);
    return n_neighbours;
}

void hypercubeANN(ofstream* file, int q_num, int probes, int n, int points_M, unsigned int radius, int d, int number_of_images) {
    unsigned int current_distance = 0;
    int maximumN = n;
    int counter = 0;
	vector<int> allPossibleNeighbours;
    int* qarray, *parray;
	string queryHash = calculateCubeG_X(d, q_num, QUERY_FILE);
	qarray = convertArray(query_cube_images[q_num], d);
	vector<pair<unsigned int, unsigned int> > BNN;

	// get the time for Hypercube
    auto startHypercube = chrono::high_resolution_clock::now();
	allPossibleNeighbours = findAllNeighboursToBeChecked(queryHash, points_M, probes);
	auto finishHypercube = chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsedHypercube = finishHypercube - startHypercube;

    // get the time for brute force
    auto startTrue = chrono::high_resolution_clock::now();
    BNN = hypercube_Full_Search(d, n, q_num, number_of_images);
    auto finishTrue = chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsedTrue = finishTrue - startTrue;

    // write in output file
	(*file) << "Query:" << q_num << endl;
	for (unsigned int i=0; i<allPossibleNeighbours.size(); i++) {
        parray = convertArray(all_cube_images[allPossibleNeighbours[i]], d);
        current_distance = manhattanDistance(qarray, parray, d);
        delete[] parray;
        if (current_distance <= radius) {
	        (*file) << "Nearest neighbour-" << counter+1 << ": " << allPossibleNeighbours[i] << endl;
	        (*file) << "distanceLSH: " << current_distance << endl;
	        (*file) << "distanceTrue: " << BNN[counter].second << endl;

		    BNN.clear();
        	maximumN--;
        	counter++;
        }
        if (maximumN == 0) break;
	}
	delete[] qarray;

	(*file) << "tLSH: " << elapsedHypercube.count() << endl;
	(*file) << "tTrue: " << elapsedTrue.count() << endl;

	allPossibleNeighbours.clear();
}