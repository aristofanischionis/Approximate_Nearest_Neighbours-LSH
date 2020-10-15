#include <string>
#include <vector>
#include "headers/handle-input.hpp"
#include "headers/process.hpp"
#include "headers/hashtable.hpp"
#include "headers/hashtable.hpp"
#include "headers/search.hpp"
using namespace std; 

unsigned char** all_images = NULL;
unsigned char** query_images = NULL;

int main(int argc, char **argv) {
    uint32_t number_of_images = 0;
    uint32_t number_of_query_images = 0;
    uint64_t d = 0;
    uint64_t d_query = 0;
    int k = SMALL_K;
	int l = SMALL_L;
	int n = SMALL_N;
	double r = SMALL_R;
    string output_file, query_file;
    vector<uint32_t> ANN;
    
    handleInput(argc, argv, &number_of_images, &d, &k, &l, &n, &r, &output_file, &query_file);
    do {
        readFile(query_file, QUERY_FILE, &number_of_query_images, &d_query);
        process(number_of_images, d, k, l, n, r);
        for (uint32_t q_num = 0; q_num < number_of_query_images; q_num++){
            ANN = approximateN_NNs(d, k, n, l, q_num, number_of_images, number_of_query_images);
        }
        handleReExecution(&number_of_images, &d, &k, &l, &n, &r, &output_file, &query_file);
    } while (true);
    // DON'T FORGET TO FREE UP ALL USED SPACE
    // free up space for all_images
    // !!make function!!
    for (uint32_t i = 0; i < number_of_images;i++){
        delete[] all_images[i];
    }
    delete[] all_images;
    for (uint32_t i = 0; i < number_of_query_images;i++){
        delete[] query_images[i];
    }
    delete[] query_images;
    deleteHashtable(l, number_of_images);
    return SUCCESS;
}