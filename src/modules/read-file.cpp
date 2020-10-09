// Function to read binary files
#include <iostream>
#include <fstream>
// #include <sstream>
#include <string>

#include "../headers/handle-input.hpp"
using namespace std;

// read the first lines of the file, that contain the metadata
void getMeta(ifstream *file) {
    uint32_t magic_number;
    uint32_t number_of_images;
    uint32_t number_of_rows;
    uint32_t number_of_columns;
    // read them from file
    (*file).read(reinterpret_cast<char *>(&magic_number), sizeof(magic_number));
    (*file).read(reinterpret_cast<char *>(&number_of_images), sizeof(number_of_images));
    (*file).read(reinterpret_cast<char *>(&number_of_rows), sizeof(number_of_rows));
    (*file).read(reinterpret_cast<char *>(&number_of_columns), sizeof(number_of_columns));
    // convert them to high endian
    magic_number = __builtin_bswap32(magic_number);
    number_of_images = __builtin_bswap32(number_of_images);
    number_of_rows = __builtin_bswap32(number_of_rows);
    number_of_columns = __builtin_bswap32(number_of_columns);
    // 
    cout << "magic_number is: " << magic_number << endl;
    cout << "number_of_images is: " << number_of_images << endl;
    cout << "number_of_rows is: " << number_of_rows << endl;
    cout << "number_of_columns is: " << number_of_columns << endl;
    return;
}

// read 784 bytes from file which are equal to an image
// return vector!
// each byte is a component and has a value between 0-255
int readImage(char* memblock) {
    return 0;
}

// handling the input file
void readFile(const std::string& filename, int file_type) {
    // Checked and I receive the filename string properly
    cout << "my file name is: " << filename << endl;
    // check if filename exists
    // ios::ate positions the pointer in the end of the file
    // this way using: file.seekg(0, ios::beg); will give us the size of the file
    ifstream file;
    file.open(filename, ios::in|ios::binary|ios::ate);
    streampos size;
    // char* memblock;
    // open file to start reading
    if (file.is_open()) {
        size = file.tellg();
        // memblock = new char[size];
        file.seekg(0, ios::beg);
        cout << "the entire file content is in memory: " << size << endl;
        // read the data according to file_type
        switch (file_type){
            case INPUT_FILE:
                // cout << "Hello Im in getme" << memblock << endl;
                getMeta(&file);
                // loop over all images to read them
                break;
            case QUERY_FILE:
                break;
            default:
                cout << "It is not the input_file or query_file" << endl;
                break;
        }
        file.close();
        // delete[] memblock;
    }
    else cout << "Unable to open file" << endl;
  return;
}