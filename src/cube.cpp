#include <iostream>
#include <fstream>
#include "headers/common.hpp"
#include "headers/cube/projection.hpp"
#include "headers/cube/handle-cube-input.hpp"
#include "headers/cube/read-cube-file.hpp"
using namespace std;

int main(int argc, char **argv) {
    uint32_t number_of_images = 0;
    uint32_t number_of_query_images = 0;
    int k = SMALL_CUBE_K;
	int n = SMALL_N;
	int points_M = POINTS_M;
	int probes = PROBES;
	unsigned int r = SMALL_R;
    uint64_t d = 0;
    uint64_t d_query = 0;
    w = 400;
    string output_file, query_file;
    ofstream o_file;

    handleCubeInput(argc, argv, &number_of_images, &d, &k, &points_M, &probes, &n, &r, &output_file, &query_file);

    o_file.open(output_file);
    if (!o_file.is_open()){
        cerr << "Output file can't be opened" << endl;
        exit(ERROR);
    }
    do {
        readCubeFile(query_file, QUERY_FILE, &number_of_query_images, &d_query, k);
        for (uint32_t q_num = 0; q_num < number_of_query_images; q_num++) {
            hypercubeANN(&o_file, q_num, probes, n, points_M, r, d, number_of_images);
        }
        w = 400;
        // calculateW_Component(d, number_of_images, number_of_query_images);
        o_file.close();
        // open output file
        o_file.open(output_file);
        if (!o_file.is_open()){
            cerr << "Output file can't be opened" << endl;
            exit(ERROR);
        }
        handleCubeReExecution(&number_of_images, &d, &k, &points_M, &probes, &n, &r, &output_file, &query_file);
        o_file.close();
    } while (true);
    // DON'T FORGET TO FREE UP ALL USED SPACE
    // free up space for all_images
    // !!make function!!
    for (uint32_t i = 0; i < number_of_images;i++) {
        delete[] all_cube_images[i];
    }
    delete[] all_cube_images;
    for (uint32_t i = 0; i < number_of_query_images;i++) {
        delete[] query_cube_images[i];
    }
    delete[] query_cube_images;
    return SUCCESS;

    // TODO: FREE UP MEMORY
}