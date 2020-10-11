#include <iostream>
#include "headers/distances.hpp"
#include "headers/handle-input.hpp"
using namespace std; 

int main(int argc, char **argv) {
    // int x[4] = { -1, 1, 3, 2 }; 
    // int y[4] = { 5, 6, 5, 3 };
    // int n = sizeof(x) / sizeof(x[0]); 
    // int n1 = sizeof(y) / sizeof(y[0]);
    
    // cout << "Success " << manhattan_distance(x, n, y, n1) << endl;
    handleInput(argc, argv);
    return SUCCESS;
}