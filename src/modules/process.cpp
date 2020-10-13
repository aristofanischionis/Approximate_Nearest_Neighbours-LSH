#include <iostream>
#include "../headers/process.hpp"
#include "../headers/manhattan-hashing.hpp"
#include "../headers/modulo.hpp"
#include "../headers/handle-input.hpp"
#include "../headers/hashtable.hpp"
using namespace std; 

// Calculate h(x) using the formula from the theory
int createH_X (uint64_t d, int image) {
    float *s_i;
    int *a_i;
    int hx = 0;
    // firstly calculate s_i components
    s_i = calculateURDComponents(d);
    // calculate a_i components
    // all_images array is globally accessible
    a_i = calculateA_IComponents(all_images[image], s_i, d);
    // then calculate hx
    hx = calculateH_XComponent(a_i, d);
    return hx;
}

// Calculate g(x) using bitwise operations
unsigned int createG_X (int* all_of_H_X, int k) {
    unsigned int gx = all_of_H_X[0];

    for (int i=1;i<k; i++) {
        gx<<=8;
        gx |= all_of_H_X[i];
    }

    return gx;
}

void process (uint32_t number_of_images, uint64_t d, int k, unsigned int L, int n, double r){
    int h_x[k];
    unsigned int g_x = 0;
    initializeHashtables(L, number_of_images);
    // now we can initialize hash tables and continue
    // we need to process every image and put it in the hashtables
    for (int l = 0; l < L; l++) {
        // for all the images
        for (uint32_t image = 0; image < number_of_images; image++) {
            for (int i = 0; i < k; i++) {
                // create h_x
                h_x[i] = createH_X(d, image);
            }
            // create g_x
            g_x = createG_X(h_x, k);
            // pass to hashtable
            // cout << "final g(x) is: " << g_x << endl;
            insertToHashtable(L, image, g_x);
        }
    }
}