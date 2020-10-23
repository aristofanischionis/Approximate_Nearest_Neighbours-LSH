#include <iostream>
#include <fstream>
#include <sys/mman.h>
#include "../../headers/handle-input.hpp"
#include "../../headers/common.hpp"
#include "../../headers/cube/projection.hpp"
#include "../../headers/cube/handle-cube-input.hpp"
using namespace std;

void readCubeFile (const string& filename, int file_type, uint32_t* number_of_images, uint64_t* d, int k) {
    long length;
    uint8_t *mmfile = openMMap(filename, length);

    uint32_t* memblockmm;
    unsigned char* buffer;
    memblockmm = (uint32_t *)mmfile; //cast file to uint32 array
    uint32_t magic_number = memblockmm[0]; // take first int
    mmfile +=4; //increment by 4 as I read a 32 bit entry and each entry in mmfile is 8 bits.
    uint32_t image_number = memblockmm[1];
    mmfile +=4;
    uint32_t number_of_rows = memblockmm[2];
    mmfile +=4;
    uint32_t number_of_columns = memblockmm[3];

    magic_number = __builtin_bswap32(magic_number);
    image_number = __builtin_bswap32(image_number);
    number_of_rows = __builtin_bswap32(number_of_rows);
    number_of_columns = __builtin_bswap32(number_of_columns);
    
    *d = number_of_columns * number_of_rows;
    *number_of_images = image_number;
    // change memblockmm to unsigned char *
    buffer = static_cast<unsigned char *>(mmfile);
    mmfile += *d;

    if (file_type == INPUT_FILE) {
        // Process input data and insert into hypercube
        string cube_g_x;
        d_space = calculateLogDspace(*d);
        projections.resize(d_space);
        all_cube_images = new unsigned char *[image_number];
        for (int image = 0; image < (int)image_number; image++) {
            all_cube_images[image] = new unsigned char[*d];
            all_cube_images[image] = &buffer[image + 4];
            mmfile += *d;
             // calculate hash of current image
            cube_g_x = calculateCubeG_X(*d, image, INPUT_FILE);
            // insert to hypercube
            insertToHypercube(cube_g_x, image);
        }
    }
    else if (file_type == QUERY_FILE) {
        // initialize the array for the query dataset
        query_cube_images = new unsigned char *[image_number];
        // loop over all images to read them
        for (unsigned int image = 0; image < image_number; image++) {
            query_cube_images[image] = new unsigned char[*d];
            query_cube_images[image] = &buffer[image + 4];
            mmfile += *d;
        }
    }

    munmap(mmfile, length);
}