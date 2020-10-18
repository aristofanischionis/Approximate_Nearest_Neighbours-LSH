#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <chrono>
#include "../headers/manhattan-hashing.hpp"
#include "../headers/distances.hpp"
#include "../headers/handle-input.hpp"
#include "../headers/modulo.hpp"
#include "../headers/hashtable.hpp"
#include "../headers/search.hpp"
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
vector<pair <unsigned int, unsigned int> > approximateN_NNs (ofstream* file, uint64_t d, int k, int n, int L, uint32_t q_num, int number_of_images, int number_of_query_images) {
    vector<pair <unsigned int, unsigned int> > n_neighbours;
    unsigned int min_distance = inf;
    unsigned int current_gp = 0;
    unsigned int current_distance = 0;
    int pos_in_hash = 0;
    int hashtable_size = number_of_images / HASHTABLE_NUMBER;
    // we start putting neighbours from farthest to closest
    int* qarray, *parray;

    auto startLSH = chrono::high_resolution_clock::now();
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
    auto finishLSH = chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsedLSH = finishLSH - startLSH;

    reverse(n_neighbours.begin(), n_neighbours.end());
    if (n_neighbours.size() > static_cast<unsigned int>(n)) n_neighbours.resize(n);
    // write in output file
    vector<pair<unsigned int, unsigned int> > BNN;

    auto startTrue = chrono::high_resolution_clock::now();
    BNN = approximateN_NNs_Full_Search(d, n, q_num, number_of_images);
    auto finishTrue = chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsedTrue = finishTrue - startTrue;

    (*file) << "Query:" << q_num << endl;
    for (unsigned int i = 0; i < n_neighbours.size(); i++){
        (*file) << "Nearest neighbour-" << i+1 << ": " << n_neighbours[i].first << endl;
        (*file) << "distanceLSH: " << n_neighbours[i].second << endl;
        (*file) << "distanceTrue: " << BNN[i].second << endl;
    }
    (*file) << "tLSH: " << elapsedLSH.count() << endl;
    (*file) << "tTrue: " << elapsedTrue.count() << endl;
    BNN.clear();
    return n_neighbours;
}

// Brute Force
vector<pair <unsigned int, unsigned int> > approximateN_NNs_Full_Search(uint64_t d, int n, uint32_t q_num, int number_of_images) {
    vector<pair <unsigned int, unsigned int> > n_neighbours;
    vector<pair <unsigned int, unsigned int> >::iterator it;
    unsigned int current_distance = 0;
    int* qarray, *parray;
    // loop over the images array
    for (int i=0; i<number_of_images; i++) {
        qarray = convertArray(query_images[q_num], d);
        parray = convertArray(all_images[i], d);
        current_distance = manhattanDistance(qarray, parray, d);
        delete[] qarray;
        delete[] parray; 
        n_neighbours.push_back(make_pair(i, current_distance));
    }
    sort(n_neighbours.begin(), n_neighbours.end(), [](const pair<unsigned int, unsigned int> &left, const pair<unsigned int, unsigned int> &right) {
        return left.second < right.second;
    });
    if (n_neighbours.size() >  static_cast<unsigned int>(n)) n_neighbours.resize(n);
    return n_neighbours;
}


// searches using range search
vector<pair <unsigned int, unsigned int> > rangeSearch(ofstream* file, uint64_t d, int k, int L, uint32_t q_num, unsigned int radius,int number_of_images, int number_of_query_images) {
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

    (*file) << "R-near neighbours:" << n_neighbours.size() << endl;
    for (unsigned int i=0; i<n_neighbours.size(); i++) {
        (*file) << n_neighbours[i].first << endl;
    }
    return n_neighbours;
}