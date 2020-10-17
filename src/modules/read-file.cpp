// Function to read binary files
#include <iostream>
#include <fstream>
#include "../headers/handle-input.hpp"
#include "../headers/hashtable.hpp"
#include "../headers/manhattan-hashing.hpp"
using namespace std;

// read the first lines of the file, that contain the metadata
void getMeta(
    ifstream *file, 
    uint32_t &magic_number, 
    uint32_t &image_number, 
    uint32_t &number_of_rows, 
    uint32_t &number_of_columns
    ) {
    // read them from file
    (*file).read(reinterpret_cast<char *>(&magic_number), sizeof(magic_number));
    (*file).read(reinterpret_cast<char *>(&image_number), sizeof(image_number));
    (*file).read(reinterpret_cast<char *>(&number_of_rows), sizeof(number_of_rows));
    (*file).read(reinterpret_cast<char *>(&number_of_columns), sizeof(number_of_columns));
    // convert them to high endian
    magic_number = __builtin_bswap32(magic_number);
    image_number = __builtin_bswap32(image_number);
    number_of_rows = __builtin_bswap32(number_of_rows);
    number_of_columns = __builtin_bswap32(number_of_columns);
}

void readImage(ifstream *file, unsigned char* image, uint64_t d) {
    unsigned char byte;
    // read one-by-one d (number_of_rows * number_of_columns) dunsigned bytes
    for (uint64_t i = 0; i < d; i++) {
        (*file).read(reinterpret_cast<char*>(&byte), 1);
        image[i] = byte;
    }
}

void initializeImageArray(ifstream *file, int file_type, uint32_t image_number, uint64_t d, int k, uint32_t number_of_images, int L) {
    if (file_type == INPUT_FILE) {
        unsigned int g_x = 0;
        // initialize the array of vector items (all_images) for input_data
        all_images = new unsigned char *[image_number];
        // loop over all images to read them
        for (uint32_t i = 0; i < image_number; i++) {
            all_images[i] = new unsigned char[d];
            readImage(file, all_images[i], d);
            // insert this image in all hashtables
            for (int l=0; l<L; l++) {
                g_x = calculateG_X(k, d, i, INPUT_FILE);
                // pass to hashtable
                insertToHashtable(l, i, g_x, number_of_images);
            }
        }
    } 
    else if (file_type == QUERY_FILE) {
        // initialize the array for the query dataset
        query_images = new unsigned char *[image_number];
        // loop over all images to read them
        for (uint32_t i = 0; i < image_number; i++) {
            query_images[i] = new unsigned char[d];
            readImage(file, query_images[i], d);
        }
    }
}

void printFiles(uint32_t number_of_images, uint32_t number_of_query_images, uint64_t d) {
    cout << "INPUT DATASET:" << endl;
    for (uint32_t i = 0; i < number_of_images; i++){
        cout << "next image" << endl;
        for (uint64_t j = 0; j < d; j++) {
            cout << static_cast<unsigned>(all_images[i][j]) << '\t';
        }
        cout << endl;
    }
    cout << "QUERY DATASET:" << endl;
    for (uint32_t i = 0; i < number_of_query_images; i++)
    {
        cout << "next image" << endl;
        for (uint64_t j = 0; j < d; j++) {
            cout << static_cast<unsigned>(query_images[i][j]) << '\t';
        }
        cout << endl;
    }
}

// handling the input file
void readFile(const string& filename, int file_type, uint32_t* image_number, uint64_t* d, int k, uint32_t number_of_images, int L) {
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
    getMeta(&file, magic_number, *image_number, number_of_rows, number_of_columns);
    *d = number_of_columns * number_of_rows;
    initializeImageArray(&file, file_type, *image_number, *d, k, number_of_images, L);
    file.close();
}