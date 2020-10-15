#include <iostream>
#include <vector>
#include "../headers/manhattan-hashing.hpp"
#include "../headers/distances.hpp"
#include "../headers/handle-input.hpp"
#include "../headers/modulo.hpp"
#include "../headers/hashtable.hpp"
using namespace std;

unsigned int* convertArray(unsigned char* array, int size) {
    unsigned int *result_array = new unsigned int(size);
    for (int i = 0; i < size;i++) {
        result_array[i] = static_cast<unsigned int>(array[i]);
    }
    return result_array;
}

// two ways to find this
// A. LSH
// B. True (brute force)
// takes a N from user 
// calls approximateNN with the correct way (A or B)
// q_num: is an index of the query to search in the query_images[]
vector<uint32_t> approximateN_NNs (uint64_t d, int k, int n, int L, uint32_t q_num, int number_of_images, int number_of_query_images) {
    unsigned int min_distance = m;
    vector<uint32_t> n_neighbours;
    unsigned int current_gp = 0;
    unsigned int current_distance = 0;
    int pos_in_hash = 0;
    int hashtable_size = number_of_images / HASHTABLE_NUMBER;
    // we start putting neighbours from farthest to closest 
    int k_th_neighbour = n;
    unsigned int* qarray, *parray;
    // for all hash_tables
    for (int l = 0; l < L; l++) {
        // calculating g(q)
        current_gp = calculateG_X(k, d, q_num, QUERY_FILE);
        pos_in_hash = customModulo(current_gp, M);
        if(pos_in_hash > hashtable_size -1) {
            // then something went wrong with g(p)
            cerr << "Calculating g(q) went wrong" << endl;
            exit(ERROR);
        }
        // loop over the bucket
        cout << "Current hashtable: " << l << endl;
        for (unsigned int h = 0; h < HashTables[l][pos_in_hash].size(); h++) {
            // calculate the Manhattan distance of q and every other image in the bucket
            // distance between HashTables[l][pos_in_hash][h], and query_image[q_num]
            qarray = convertArray(query_images[q_num], number_of_query_images);
            parray = convertArray(all_images[HashTables[l][pos_in_hash][h]], number_of_images);
            current_distance = manhattanDistance(qarray, parray, d);
            delete[] qarray;
            delete[] parray;
            if((current_distance < min_distance) && (k_th_neighbour > 0)) {
                // we keep this neighbour and also keep the distance?!
                n_neighbours.push_back(q_num);
                cout << "K-th neighbour is: " << k_th_neighbour << " current_distance: " << current_distance << " q_num: " << q_num << endl;
                min_distance = current_distance;
                k_th_neighbour--;
            }

            if(k_th_neighbour == 0)
                return n_neighbours;

            // take into account a maximum of (10 * L) points in each hashtable
            if (h > static_cast<unsigned int>(10*L)) {
                // return n_neighbours;
                // break the loop to continue with next hashtable
                break;
            }
        }
        // return n_neighbours;
        // finished with this hash table
    }
    return n_neighbours;
}

// searches using range search Brute force
void rangeSearch () {
    
}