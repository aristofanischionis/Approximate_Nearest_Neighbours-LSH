#include <iostream>
#include <fstream>
#include <string>
#include "../../headers/handle-input.hpp"
#include "../../headers/common.hpp"
#include "../../headers/cube/projection.hpp"
#include "../../headers/cube/handle-cube-input.hpp"
using namespace std;

void initializeImageArray(ifstream *file, int file_type, uint32_t number_of_images, uint64_t d, int k) {
    if (file_type == INPUT_FILE) {
        // Process input data and insert into hash_tables
        // it is wrong to return <int>, find where is the best to store it ? maybe bitstring?
        string cube_g_x;
        d_space = calculateLogDspace(d);
        projections.resize(d_space);
        // initialize the array of vector items (all_images) for input_data
        all_cube_images = new unsigned char *[number_of_images];
        // loop over all images to read them
        for (uint32_t i = 0; i < number_of_images; i++) {
            all_cube_images[i] = new unsigned char[d];
            readImage(file, all_cube_images[i], d);
            // insert this image in hypercube
            cube_g_x = calculateCubeG_X(d, i, INPUT_FILE);
            // pass to hypercube
            insertToHypercube(cube_g_x, (int)i);
        }
        printHypercube();
    }
    else if (file_type == QUERY_FILE) {
        // initialize the array for the query dataset
        query_cube_images = new unsigned char *[number_of_images];
        // loop over all images to read them
        for (uint32_t i = 0; i < number_of_images; i++) {
            query_cube_images[i] = new unsigned char[d];
            readImage(file, query_cube_images[i], d);
        }
    }
}

void readCubeFile (const string& filename, int file_type, uint32_t* number_of_images, uint64_t* d, int k) {
    ifstream file;
    uint32_t magic_number = 0;
    uint32_t number_of_rows = 0;
    uint32_t number_of_columns = 0;
    // open file to start reading
    file.open(filename, ios::in|ios::binary);
    if (!file.is_open()){
        cerr << "Unable to open file" << endl;
        exit(ERROR);
    }
    file.seekg(0, ios::beg);
    // start reading from file
    getMeta(&file, magic_number, *number_of_images, number_of_rows, number_of_columns);
    *d = number_of_columns * number_of_rows;
    initializeImageArray(&file, file_type, *number_of_images, *d, k);
    file.close();
}