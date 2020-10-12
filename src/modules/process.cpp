#include <iostream>
#include "../headers/process.hpp"
#include "../headers/manhattan-hashing.hpp"
#include "../headers/modulo.hpp"
#include "../headers/handle-input.hpp"
using namespace std; 

void process (uint32_t number_of_images, uint64_t d){
    cout << "number_of_images is: " << number_of_images << endl;
    for (int i = 0; i < number_of_images; i++){
        cout << "-------------------new image---------------------------" << endl;
        for (int j = 0; j < d; j++)
        {
            cout << all_images[i][j] << "\t";
        }
        cout << "--------------------------------------------------" << endl;
    }
    // now we can initialize hash tables and continue

    // 
}