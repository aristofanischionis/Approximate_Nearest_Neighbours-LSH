#include <iostream>
#include <cstdlib>
#include <string>
#include <algorithm>
#include "headers/common.hpp"

using namespace std;

int main(int argc, char **argv) {
	string output_file;
	string input_file;
	string config_file;
	string method;

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
			method = argv[i+1];
		}
	}
	// TODO: Read from config file


	// Make it to upper
	transform(method.begin(), method.end(),method.begin(), ::toupper);

	if (method == "CLASSIC") {
		// TDDO: Run classic
	}
	else if (method == "LSH") {
		if (!system("cd - && ./lsh"))
			cerr << "Something went wrong on system" <<endl;
	}
	else if (method == "HYPERCUBE") {
		if (!system("cd - && ./cube"))
			cerr << "Something went wrong on system" <<endl;
	}

	return SUCCESS;
}