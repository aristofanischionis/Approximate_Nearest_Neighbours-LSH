#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include "headers/common.hpp"
#include "headers/kmeansPP/kmeansPP.hpp"

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
	int K_medians = -1;
	int L = 3;
	int k_LSH = 4;
	int points_M = 10;
	int k_Hypercube = 3;
	int probes = 2;
	uint32_t number_of_images = 0;
	uint64_t d = 0;
	vector<pair<int*, vector<int> > > clusters;

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
			// Do staff for complete
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
	// Make it to upper
	transform(method.begin(), method.end(),method.begin(), ::toupper);

	if (method == "CLASSIC") {
		clusters = kmeansPP(K_medians, number_of_images, d);
	}
	// else if (method == "LSH") {
	// 	strcpy(command, "cd - && ./lsh ");
	// 	strcat(command, "-d ");
	// 	strcat(command, "-q ");
	// 	strcat(command, "-k ");
	// 	strcat(command, "-L ");
	// 	strcat(command, "-o ");
	// 	strcat(command, "-N ");
	// 	strcat(command, "-R ");
	// 	if (!system(command))
	// 		cerr << "Something went wrong on system" <<endl;
	// }
	// else if (method == "HYPERCUBE") {
	// 	if (!system("cd - && ./cube"))
	// 		cerr << "Something went wrong on system" <<endl;
	// }

	return SUCCESS;
}

