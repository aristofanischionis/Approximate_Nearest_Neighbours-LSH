// Function to handle the input given from command line
#include <iostream>
#include <sstream>
#include <cmath>
#include <unordered_map>
#include "../../headers/common.hpp"
#include "../../headers/cube/handle-cube-input.hpp"
#include "../../headers/cube/read-cube-file.hpp"

using namespace std;

int d_space;
unsigned char** all_cube_images = NULL;
unsigned char** query_cube_images = NULL;
// it takes h_i(p) and bitstring (bucket in Hypercube)
vector<unordered_map<int, int> > projections;
multimap <std::string, int> Hypercube;

void handleCubeReExecution (
	uint32_t *number_of_images, 
	uint64_t *d,
	int *k,
	int *points_M,
	int *probes,
	int *n,
	unsigned int *r,
	string *output_file,
	string *query_file
	) {
	
	string input_file, param;
	cout << "Please enter new parameters for the program to re-execute or press enter to exit" << endl;
	string input;
	char split_char = ' ';
	getline(cin, input);
	if (input.size() == 0)
		exit(SUCCESS);
	// Here the least amount of arguments are 6
	// We don't pass the executable name as parameter
	if (input.size() < 6) {
		cout << "You need to provide the path of the files" << endl;
		exit(ERROR);
	}

	// stringstream class token
	stringstream token(input);
	// tokenize the input and store the values
	while (getline(token, param, split_char)) {
		if (param == "-k") {
			getline(token, param, split_char);
			stringstream intValue(param);
			intValue >> *k;
		}
		else if (param == "-M") {
			getline(token, param, split_char);
			stringstream intValue(param);
			intValue >> *points_M;
		}
		else if (param == "-probes") {
			getline(token, param, split_char);
			stringstream intValue(param);
			intValue >> *probes;
		}
		else if (param == "-N")	{
			getline(token, param, split_char);
			stringstream intValue(param);
			intValue >> *n;
		}
		else if (param == "-R")	{
			getline(token, param, split_char);
			stringstream intValue(param);
			intValue >> *r;
		}
		else if (param == "-o")	{
			getline(token, param, split_char);
			*output_file = param;
		}
		else if (param == "-d") {
			getline(token, param, split_char);
			input_file = param;
		}
		else if (param == "-q")	{
			getline(token, param, split_char);
			*query_file = param;
		}
	}
	// Check if the files are provided
	if (input_file.empty())	{
		cout << "You need to provide the input_file path" << endl;
		exit(ERROR);
	}
	if (output_file->empty()) {
		cout << "You need to provide the output_file path" << endl;
		exit(ERROR);
	}
	if (query_file->empty()) {
		cout << "You need to provide the query_file path" << endl;
		exit(ERROR);
	}

	if (*k < 2)	{
		cerr << "The number k should be more than 2, from theory, ideally should be 4" << endl;
		exit(ERROR);
	}
	// M as given from theory
	M = pow(2, 32/(*k));
	m = M/2 - 1;
	readCubeFile(input_file, INPUT_FILE, number_of_images, d, *k);
}

void handleCubeInput(
	int argc, 
	char **argv, 
	uint32_t *number_of_images, 
	uint64_t *d,
	int *k,
	int *points_M,
	int *probes,
	int *n,
	unsigned int *r,
	string *output_file,
	string *query_file
	){
	string input_file;
	// First we need to check for the least amount of arguments required
	// Which are 7 since we need 3 files with their param and the executable
	if (argc < 7) {
		cerr << "You need to provide the path of the files" << endl;
		exit(ERROR);
	}	
	string param = argv[1];

	// get the path files
	if (param != "-d") {
		cerr << "You need to provide the input_file path" << endl;
		exit(ERROR);
	}
	input_file = argv[2];

 	param = argv[3];
	if (param != "-q") {
		cerr << "You need to provide the query_file path" << endl;
		exit(ERROR);
	}
	*query_file = argv[4];

	for (int i = 5; i < argc; i++) {
		param = argv[i];
		if (!argv[i+1]) exit(ERROR);
		if (param == "-k") *k = atoi(argv[++i]);
		else if (param == "-M") *points_M = atoi(argv[++i]);
		else if (param == "-probes") *probes = atoi(argv[++i]);
		else if (param == "-N") *n = atoi(argv[++i]);
		else if (param == "-R") *r = atof(argv[++i]);
		else if (param == "-o") *output_file = argv[++i];
	}

	if (output_file->empty()) {
		cerr << "You need to provide the output_file path" << endl;
		exit(ERROR);
	}
	
	if (*k < 2) {
		cerr << "The number k should be more than 2, from theory, ideally should be 4" << endl;
		exit(ERROR);
	}
	// M as given from theory
	M = pow(2, 32/(*k));
	m = M/2 - 1;

	// read data from the input_file
	readCubeFile(input_file, INPUT_FILE, number_of_images, d, *k);
	// returning these values to main to continue execution
}