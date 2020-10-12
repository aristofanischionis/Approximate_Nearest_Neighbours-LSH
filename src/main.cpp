#include <iostream>
#include "headers/handle-input.hpp"
#include "headers/process.hpp"

using namespace std; 

unsigned char** all_images = NULL;
int main(int argc, char **argv) {
    uint32_t number_of_images = 0;
    uint64_t d = 0;
    handleInput(argc, argv, &number_of_images, &d);
    process(number_of_images, d);
    // Here we start the loop after the first execution of the program
    while(true) {
        handleReExecution(&number_of_images, &d);
        process(number_of_images, d);
    }
    return SUCCESS;
}