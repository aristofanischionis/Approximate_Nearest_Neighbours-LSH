#include <iostream>
#include <fstream>
#include <algorithm>
#include <chrono>
#include <cmath>
#include "headers/kmeansPP/kmeansPP.hpp"
#include "headers/common.hpp"

using namespace std;

// read conf file
void readConfFile(string filename, int* K_medians, int *L, int *k_LSH, int *points_M, int *k_Hypercube, int *probes) {
	ifstream confFile(filename);
	string param;
	int value;

	while (confFile >> param >> value) {
		if(param == "number_of_clusters:") {
			*K_medians = value;
		}
		else if(param == "number_of_vector_hash_tables:") {
			*L = value;
		}
		else if(param == "number_of_vector_hash_functions:") {
			*k_LSH = value;
		}
		else if(param == "max_number_M_hypercube:") {
			*points_M = value;
		}
		else if(param == "number_of_hypercube_dimensions:") {
			*k_Hypercube = value;
		}
		else if(param == "number_of_probes:") {
			*probes = value;
		}
	}
}

int main(int argc, char **argv) {
	string output_file;
	string input_file;
	string config_file;
	string method;
	bool complete_flag = false;
	int K_medians = -1;
	int L = 3;
	int k_LSH = 4;
	int points_M = 10;
	int k_Hypercube = 3;
	int probes = 2;
	uint32_t number_of_images = 0;
	uint64_t d = 0;
	vector<pair<int*, vector<int> > > clusters;
	vector<double> s_i;
    ofstream o_file;

	if (argc < 9) {
		cerr << "A file path or method is missing" << endl;
		exit(ERROR);
	}

	string param = argv[1];
	// get the path files
	if (param != "-i") {
		cerr << "You need to provide the input_file path" << endl;
		exit(ERROR);
	}
	input_file = argv[2];

	param = argv[3];
	if (param != "-c") {
		cerr << "You need to provide the configuration_file path" << endl;
		exit(ERROR);
	}
	config_file = argv[4];

	param = argv[5];
	if (param != "-o") {
		cerr << "You need to provide the output_file path" << endl;
		exit(ERROR);
	}
	output_file = argv[6];
	
	for (int i = 7; i < argc; i++) {
		param = argv[i];
		if (!argv[i+1]) exit(ERROR);
		if (param == "-complete") {
			complete_flag = true;
		}
		else if (param == "-m") {
			method = argv[++i];
		}
	}

	readConfFile(config_file, &K_medians, &L, &k_LSH, &points_M, &k_Hypercube, &probes);
	readClusterFile(input_file, &number_of_images, &d);

	if (K_medians < 1) {
		cerr << "You have to give a value for K-medians" << endl;
		exit(ERROR);
	}

	w=400;
	// Make it to upper
	transform(method.begin(), method.end(),method.begin(), ::toupper);

	// M as given from theory
	if (method == "LSH")
		M = pow(2, 32/(k_LSH));
	else
		M = pow(2, 32/(k_Hypercube));

	m = M/2 - 1;
	auto start = chrono::system_clock::now();
	clusters = kmeansPP(L, k_LSH, K_medians, number_of_images, d, method, points_M, probes);
	s_i = silhouette(clusters, d);

	auto end = chrono::system_clock::now();
	auto elapsed = chrono::duration<double>(end - start);

    // open output file
    o_file.open(output_file);
    if (!o_file.is_open()) {
        cerr << "Output file can't be opened" << endl;
        exit(ERROR);
    }

    // Write to file 
    if (method == "CLASSIC")
    	o_file << "Algorithm: " << method << endl;
    else
    	o_file << "Algorithm: " << "Range Search "  << method << endl;
    for (unsigned int i=0; i < clusters.size(); i++) {
	    if (complete_flag) {
	    	o_file << "CLUSTER-" << i+1 << " { centroid: [";
	    	for (uint64_t j=0; j < d - 1; j++) {
	    		o_file << clusters[i].first[j] << ", ";
	    	}
	    	o_file << clusters[i].first[d - 1] << "], [";
	    	for (uint64_t j=0; j < clusters[i].second.size() - 1; j++) {
	    		o_file << clusters[i].second[j] << ", ";
	    	}
	    	o_file <<clusters[i].second[clusters[i].second.size() - 1] << "]" << endl;
	    }
	    else {
	    	o_file << "CLUSTER-" << i+1 << " {size: " << clusters[i].second.size() << ", centroid: [";
	    	for (uint64_t j=0; j < d - 1; j++) {
	    		o_file << clusters[i].first[j] << ", ";
	    	}
	    	o_file << clusters[i].first[d - 1] << "] }" << endl;
	    }
    }
    o_file << "clustering_time: " << elapsed.count() << " seconds" <<endl;

    o_file << "Silhouette: [";
    for (unsigned int i=0; i < s_i.size() - 1; i++)
    	o_file << s_i[i] << ", ";
    o_file << s_i[s_i.size() - 1] << "]";

    o_file.close();
    s_i.clear();
    clusters.clear();
	return SUCCESS;
}

