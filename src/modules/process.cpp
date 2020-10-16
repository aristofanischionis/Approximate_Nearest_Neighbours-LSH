#include <iostream>
#include "../headers/process.hpp"
#include "../headers/manhattan-hashing.hpp"
#include "../headers/modulo.hpp"
#include "../headers/handle-input.hpp"
#include "../headers/hashtable.hpp"
using namespace std;

void process (uint32_t number_of_images, uint64_t d, int k, int L, int n, unsigned int r){
    unsigned int g_x = 0;
    // now we can initialize hash tables and continue
    initializeHashtables(L, number_of_images);
    
    for (int l=0; l<L; l++) {
        // we process every image and put it in the hashtables
        for (uint32_t image = 0; image < number_of_images; image++) {
            g_x = calculateG_X(k, d, image, INPUT_FILE);
            // pass to hashtable
            insertToHashtable(l, image, g_x, number_of_images);
        }
    }
    // printHashtable(L, number_of_images);
}