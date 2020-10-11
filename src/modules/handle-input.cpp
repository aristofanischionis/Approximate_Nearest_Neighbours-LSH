// Function to handle the input given from command line
#include <iostream>
#include <sstream>
#include <string>
#include "../headers/handle-input.hpp"
#include "../headers/manhattan-hashing.hpp"
using namespace std;

int w;
unsigned long M;

void handleInput(int argc, char **argv){
	// First we need to check for the least amount of arguments required
	// Which are 7 since we need 3 files with their param and the executable
	if (argc < 7){
		cout << "You need to provide the path of the files" << endl;
		exit(ERROR);
	}	

	// Initialize default values
	int k = 4;
	int l = 5;
	int n = 1;
	double r = 1.0;
	string input_file, output_file, query_file;
	string param = argv[1];
	// get the path files
	if (param != "-d"){
		cout << "You need to provide the input_file path" << endl;
		exit(ERROR);
	}
	input_file = argv[2];

 	param = argv[3];
	if (param != "-q"){
		cout << "You need to provide the query_file path" << endl;
		exit(ERROR);
	}
	query_file = argv[4];

	for (int i = 5; i < argc; i++){
		param = argv[i];
		if (!argv[i+1]) exit(ERROR);
		if (param == "-k") k = atoi(argv[++i]);
		else if (param == "-L") l = atoi(argv[++i]);
		else if (param == "-N") n = atoi(argv[++i]);
		else if (param == "-R") r = atof(argv[++i]);
		else if (param == "-o") output_file = argv[++i];
	}

	if (output_file.empty()){
		cout << "You need to provide the output_file path" << endl;
		exit(ERROR);
	}
	//Here we call a function to do the work for input_file
	w = static_cast<int>(4*r);
	M = pow(2, 32/k);
	readFile(input_file, INPUT_FILE);

	// Here we start the loop after the first execution of the program
	while (true){
		cout << "Please enter new parameters for the program to re-execute or press enter to exit" << endl;
		string input;
		char split_char = ' ';
		getline(cin, input);
		if (input.size() == 0) exit(SUCCESS);
		// Here the least amount of arguments are 6
		// We don't pass the executable name as parameter
		if (input.size() < 6){
			cout << "You need to provide the path of the files" << endl;
			continue;
		}

		// Update default values
		k = 4;
		l = 5;
		n = 1;
		r = 1.0;

		// clear the strings
		output_file.clear();
		input_file.clear();
		query_file.clear();
		param.clear();

		// stringstream class token
	    stringstream token(input); 
	    // tokenize the input and store the values
		while (getline(token, param, split_char)){
			if (param == "-k"){
	        	getline(token, param, split_char);
	    		stringstream intValue(param);
	        	intValue >> k;
	        }
			else if (param == "-L"){
	        	getline(token, param, split_char);
	    		stringstream intValue(param);
	        	intValue >> l;
	        }
			else if (param == "-N"){
	        	getline(token, param, split_char);
	    		stringstream intValue(param);
	        	intValue >> n;
	        }
			else if (param == "-R"){
	        	getline(token, param, split_char);
	    		stringstream intValue(param);
	        	intValue >> r;
	        }
			else if (param == "-o"){
	        	getline(token, param, split_char);
 				output_file = param;
	        }
			else if (param == "-d"){
	        	getline(token, param, split_char);
 				input_file = param;
	        }
			else if (param == "-q"){
	        	getline(token, param, split_char);
 				query_file = param;
	        }
		}
		// Check if the files are provided
	    if (input_file.empty()){
			cout << "You need to provide the input_file path" << endl;
			continue;
		}
		if (output_file.empty()){
			cout << "You need to provide the output_file path" << endl;
			continue;
		}
		if (query_file.empty()){
			cout << "You need to provide the query_file path" << endl;
			continue;
		}
		readFile(input_file, INPUT_FILE);
	}
}