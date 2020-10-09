// Function to handle the input given from command line
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

void handleInput(int argc, char **argv){

	// First we need to check for the least amount of arguments required
	// Which are 7 since we need 3 files with their param and the executable
	if (argc < 7){
		cout << "You need to provide the path of the files" << endl;
		exit(0);
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
		exit(0);
	}
	input_file = argv[2];

 	param = argv[3];
	if (param != "-q"){
		cout << "You need to provide the query_file path" << endl;
		exit(0);
	}
	query_file = argv[4];

	for (int i = 5; i < argc; i++){
		param = argv[i];
		if (param == "-k") k = atoi(argv[i+1]);
		else if (param == "-L") l = atoi(argv[i+1]);
		else if (param == "-N") n = atoi(argv[i+1]);
		else if (param == "-R") r = atof(argv[i+1]);
		else if (param == "-o") output_file = argv[i+1];
	}

	if (output_file.empty()){
		cout << "You need to provide the output_file path" << endl;
		exit(0);
	}

	while (true){
		cout << "Please enter new parameters for the program to re-execute or press enter to exit" << endl;
		string input;
		char split_char = ' ';
		getline(cin, input);
		if (input.size() == 0) exit(0);
		// Here the least amount of arguments are 6
		// We don't pass the executable name as parameter
		if (input.size() < 6){
			cout << "You need to provide the path of the files" << endl;
			continue;
		}

		// Update values
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

		//Here we call a function to do the work for input_file
	}
}