#include <iostream>
#include <vector>
#include <algorithm>
#include "../headers/manhattan-hashing.hpp"
#include "../headers/distances.hpp"
#include "../headers/handle-input.hpp"
#include "../headers/modulo.hpp"
#include "../headers/hashtable.hpp"
using namespace std;

int* convertArray(unsigned char* array, int size) {
    int *result_array = new int [size];
    for (int i = 0; i < size;i++) {
        result_array[i] = static_cast<int>(array[i]);
    }
    return result_array;
}

// two ways to find this
// A. LSH
// B. True (brute force)
// takes a N from user 
// calls approximateNN with the correct way (A or B)
// q_num: is an index of the query to search in the query_images[]
vector<pair <unsigned int, unsigned int> > approximateN_NNs (uint64_t d, int k, int n, int L, uint32_t q_num, int number_of_images, int number_of_query_images) {
    vector<pair <unsigned int, unsigned int> > n_neighbours;
    unsigned int min_distance = inf;
    unsigned int current_gp = 0;
    unsigned int current_distance = 0;
    int pos_in_hash = 0;
    int hashtable_size = number_of_images / HASHTABLE_NUMBER;
    // we start putting neighbours from farthest to closest
    int* qarray, *parray;
    // for all hash_tables
    for (int l = 0; l < L; l++) {
        // calculating g(q)
        current_gp = calculateG_X(k, d, q_num, QUERY_FILE);

        pos_in_hash = customModulo(current_gp, hashtable_size);
        if (pos_in_hash > hashtable_size - 1) {
            // then something went wrong with g(p)
            cerr << "Calculating g(q) went wrong" << endl;
            exit(ERROR);
        }
        // loop over the bucket
        for (unsigned int h = 0; h < HashTables[l][pos_in_hash].size(); h++) {
            // calculate the Manhattan distance of q and every other image in the bucket
            // distance between HashTables[l][pos_in_hash][h], and query_image[q_num]
            qarray = convertArray(query_images[q_num], d);
            parray = convertArray(all_images[HashTables[l][pos_in_hash][h]], d);
            current_distance = manhattanDistance(qarray, parray, d);
            delete[] qarray;
            delete[] parray;
            if (current_distance < min_distance) {
                n_neighbours.push_back(make_pair(HashTables[l][pos_in_hash][h], current_distance));
                min_distance = current_distance;
            }
            // take into account a maximum of (10 * L) points in each hashtable
            if (h > static_cast<unsigned int>(10*L)) {
                // break the loop to continue with next hashtable
                break;
            }
        }
        // finished with this hash table
    }
    reverse(n_neighbours.begin(), n_neighbours.end());
    if (n_neighbours.size() > static_cast<unsigned int>(n)) n_neighbours.resize(n);
    return n_neighbours;
}

// Brute Force
vector<pair <unsigned int, unsigned int> > approximateN_NNs_Full_Search(uint64_t d, int n, uint32_t q_num, int number_of_images, int number_of_query_images) {
    vector<pair <unsigned int, unsigned int> > n_neighbours;
    vector<pair <unsigned int, unsigned int> >::iterator it;
    unsigned int min_distance = inf;
    unsigned int current_distance = 0;
    int* qarray, *parray;
    // loop over the images array
    for (int i=0; i<number_of_images; i++) {
        qarray = convertArray(query_images[q_num], d);
        parray = convertArray(all_images[i], d);
        current_distance = manhattanDistance(qarray, parray, d);
        delete[] qarray;
        delete[] parray;
        if (current_distance < min_distance) {
            unsigned int temp = static_cast<unsigned int>(i);
                it = find_if(
                    n_neighbours.begin(),
                    n_neighbours.end(),
                    [&temp](const pair<unsigned int, unsigned int> &current_pair)
                    { return current_pair.first == temp; });
                // if item NOT exists, then push this item in the vector
                if(it == n_neighbours.end()){
                    n_neighbours.push_back(make_pair(temp, current_distance));
                }
            min_distance = current_distance;
        }
    }
    sort(n_neighbours.begin(), n_neighbours.end(), [](const pair<unsigned int, unsigned int> &left, const pair<unsigned int, unsigned int> &right) {
        return left.second < right.second;
    });
    if (n_neighbours.size() >  static_cast<unsigned int>(n)) n_neighbours.resize(n);
    return n_neighbours;
}


// searches using range search
vector<pair <unsigned int, unsigned int> > rangeSearch (uint64_t d, int k, int n, int L, uint32_t q_num, unsigned int radius,int number_of_images, int number_of_query_images) {
    vector<pair <unsigned int, unsigned int> > n_neighbours;
    vector<pair <unsigned int, unsigned int> >::iterator it;
    unsigned int current_gp = 0;
    unsigned int current_distance = 0;
    int pos_in_hash = 0;
    int hashtable_size = number_of_images / HASHTABLE_NUMBER;
    // we start putting neighbours from farthest to closest
    int* qarray, *parray;
    // for all hash_tables
    for (int l = 0; l < L; l++) {
        // calculating g(q)
        current_gp = calculateG_X(k, d, q_num, QUERY_FILE);
        pos_in_hash = customModulo(current_gp, hashtable_size);
        if (pos_in_hash > hashtable_size - 1) {
            // then something went wrong with g(p)
            cerr << "Calculating g(q) went wrong" << endl;
            exit(ERROR);
        }
        // loop over the bucket
        for (unsigned int h = 0; h < HashTables[l][pos_in_hash].size(); h++) {
            // calculate the Manhattan distance of q and every other image in the bucket
            // distance between HashTables[l][pos_in_hash][h], and query_image[q_num]
            qarray = convertArray(query_images[q_num], d);
            parray = convertArray(all_images[HashTables[l][pos_in_hash][h]], d);
            current_distance = manhattanDistance(qarray, parray, d);
            delete[] qarray;
            delete[] parray;
            if (current_distance < radius) {
                // search if there is already inside
                // using lambda function
                unsigned int temp = HashTables[l][pos_in_hash][h];
                it = find_if(
                    n_neighbours.begin(),
                    n_neighbours.end(),
                    [&temp](const pair<unsigned int, unsigned int> &current_pair)
                    { return current_pair.first == temp; });
                // if item NOT exists, then push this item in the vector
                if(it == n_neighbours.end()){
                    n_neighbours.push_back(make_pair(temp, current_distance));
                }
            }
            // take into account a maximum of (10 * L) points in each hashtable
            if (h > static_cast<unsigned int>(10*L)) {
                // break the loop to continue with next hashtable
                break;
            }
        }
    }
    sort(n_neighbours.begin(), n_neighbours.end(), [](const pair<unsigned int, unsigned int> &left, const pair<unsigned int, unsigned int> &right) {
        return left.second < right.second;
    });
    if (n_neighbours.size() >  static_cast<unsigned int>(n)) n_neighbours.resize(n);
    return n_neighbours;
}