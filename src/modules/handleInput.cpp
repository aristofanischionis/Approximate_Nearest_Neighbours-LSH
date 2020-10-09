// Function to handle the input given from command line
#include <iostream>
#include <sstream>
#include <string>
#include <cstring>

using namespace std;

void handleInput(int argc, char **argv){

	// Initialize default values
	int k = 4;
	int l = 5;
	int n = 1;
	double r = 1.0;
	string input_file, output_file, query_file, param = argv[1];
	// get the path files
	if (param != "-d"){
		cout << "You need to provide the input_file path" << endl;
		// continue;
	}
	input_file = argv[2];

 	param = argv[3];
	if (param != "-q"){
		cout << "You need to provide the query_file path" << endl;
		// continue;
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
		cout << "You need to provide the output path" << endl;
		exit(0);
	}

	while(true){
		cout << "Please enter new parameters for the program to re-execute or press enter to exit" << endl;
		string input;
		char split_char = ' ';
		getline(cin, input);
		if (input.size() == 0) exit(0);

		// Initialize default values
		int k = 4;
		int l = 5;
		int n = 1;
		double r = 1.0;

		// clear the strings
		output_file.clear();
		input_file.clear();
		query_file.clear();
		param.clear();

		// stringstream class token
	    stringstream token(input); 
	    
	    // tokenize the input and store the values
		while(getline(token, param, split_char)){
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
	}
}