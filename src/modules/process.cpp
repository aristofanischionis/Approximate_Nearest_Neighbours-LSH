#include <iostream>
#include "../headers/process.hpp"
#include "../headers/manhattan-hashing.hpp"
#include "../headers/modulo.hpp"
#include "../headers/handle-input.hpp"
using namespace std; 

int createH_X (uint64_t d) {
    float *s_i;
    int *a_i;
    int hx = 0;
    // firstly calculate s_i components
    s_i = calculateURDComponents(d);
    // calculate a_i components
    // FIX the x_i_array
    // the all_images is globally accessible
    a_i = calculateA_IComponents(x_i_array, s_i, d);
    // then calculate hx
    hx = calculateH_XComponent(a_i, d);
    return hx;
}

int createG_X (int* all_of_H_X) {
    int gx = 0;
    // concatenate bitwise or etc
    return gx;
}
void process (uint32_t number_of_images, uint64_t d, int k, int L, int n, double r){
    // cout << "number_of_images is: " << number_of_images << endl;
    // for (int i = 0; i < number_of_images; i++) {
    //     cout << "-------------------new image---------------------------" << endl;
    //     for (int j = 0; j < d; j++)
    //     {
    //         cout << all_images[i][j] << "\t";
    //     }
    //     cout << "--------------------------------------------------" << endl;
    // }
    int h_x[k];
    int g_x = 0;
    // now we can initialize hash tables and continue
    for (int l = 0; l < L; l++){
        for (int i = 0; i < k; i++){
            // create h_x
            h_x[i] = createH_X(d);
        }
        // create g_x
        g_x = createG_X(h_x);
        // create hash tables
    }
    // 
}