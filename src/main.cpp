#include <iostream>
#include <string>
#include "headers/handle-input.hpp"
#include "headers/process.hpp"

using namespace std; 

unsigned char** all_images = NULL;
int main(int argc, char **argv) {
    uint32_t number_of_images = 0;
    uint64_t d = 0;
    int k = SMALL_K;
	int l = SMALL_L;
	int n = SMALL_N;
	double r = SMALL_R;
    string output_file, query_file;
    handleInput(argc, argv, &number_of_images, &d, &k, &l, &n, &r, &output_file, &query_file);
    process(number_of_images, d, k, l, n, r);
    // Here we start the loop after the first execution of the program
    while(true) {
        handleReExecution(&number_of_images, &d, &k, &l, &n, &r, &output_file, &query_file);
        process(number_of_images, d, k, l, n, r);
    }
    return SUCCESS;
}