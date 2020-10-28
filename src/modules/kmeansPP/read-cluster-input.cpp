#include <iostream>
#include <fstream>
#include <sys/mman.h>
#include "../../headers/handle-input.hpp"
#include "../../headers/common.hpp"
#include "../../headers/kmeansPP/kmeansPP.hpp"
#include "../../headers/manhattan-hashing.hpp"

using namespace std;
int** cluster_images;

void readClusterFile (const string& filename, uint32_t* number_of_images, uint64_t* d) {
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

    cluster_images = new int *[image_number];
    unsigned char *temp;
    temp = new unsigned char[*d];
    // loop over all images to read them
    for (unsigned int image = 0; image < image_number; image++) {
        cluster_images[image] = new int[*d];
        temp = &buffer[image + 4];
        cluster_images[image] = convertArray(temp, *d);
        mmfile += *d;
    }

    munmap(mmfile, length);
}