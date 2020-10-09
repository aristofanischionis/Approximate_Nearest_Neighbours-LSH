// Function to read binary files
#include <iostream>
#include <fstream>
#include <vector> 
#include <string>

#include "../headers/handle-input.hpp"
using namespace std;

// read the first lines of the file, that contain the metadata
void getMeta(
    ifstream *file, 
    uint32_t &magic_number, 
    uint32_t &number_of_images, 
    uint32_t &number_of_rows, 
    uint32_t &number_of_columns
    ) {
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
    return;
}

// read 784 bytes from file which are equal to an image
// return vector!
// each byte is a component and has a value between 0-255
// the vector stores 'unsigned char', because it's the most efficient
// unsigned char is a number between 0-255
// alternatively we could use uint8_t (but needs include of a library)
// BE CAREFUL WE PROBABLY NEED TO DO SOMETHING WITH THIS 28*28 
// I'M NOT SURE HOW WE ARE SUPPOSED TO CREATE THE IMAGE pff
vector<unsigned char> readImage(ifstream *file) {
    vector<unsigned char> image;
    unsigned char byte;
    int i = 0;
    // read one-by-one 784 (28*28) unsigned bytes
    for (i = 0; i < 784; i++){
        (*file).read(reinterpret_cast<char*>(&byte), 1);
        // with the following cout we see that most of the bytes have the value of 0
        // but some of them have values like 15, 235, 204, 124, etc
        // cout << "byte is: " << static_cast<unsigned>(byte) << endl;
        image.push_back(byte);
    }
    return image;
}

// handling the input file
void readFile(const std::string& filename, int file_type) {
    // Checked and I receive the filename string properly
    ifstream file;
    // an array of vectors 
    vector<unsigned char>* all_images;
    uint32_t i = 0;
    uint32_t magic_number = 0;
    uint32_t number_of_images = 0;
    uint32_t number_of_rows = 0;
    uint32_t number_of_columns = 0;

    cout << "my file name is: " << filename << endl;

    file.open(filename, ios::in|ios::binary);
    // open file to start reading
    if (file.is_open()) {
        // memblock = new char[size];
        file.seekg(0, ios::beg);
        // read the data according to file_type
        switch (file_type){
            case INPUT_FILE:
                getMeta(&file, magic_number, number_of_images, number_of_rows, number_of_columns);
                cout << "magic_number is: " << magic_number << endl;
                cout << "number_of_images is: " << number_of_images << endl;
                cout << "number_of_rows is: " << number_of_rows << endl;
                cout << "number_of_columns is: " << number_of_columns << endl;
                // initialize an array of vector items (all_images)
                all_images = new vector<unsigned char>[number_of_images];
                // loop over all images to read them
                for (i = 0; i < number_of_images; i++){
                    all_images[i] = readImage(&file);
                }
                break;
            case QUERY_FILE:
                break;
            default:
                cout << "It is not the input_file or query_file" << endl;
                break;
        }
        file.close();
        // free-up memory space
        for (i = 0; i < number_of_images; i++){
            all_images[i].clear();
        }
        delete[] all_images;
    }
    else cout << "Unable to open file" << endl;
  return;
}