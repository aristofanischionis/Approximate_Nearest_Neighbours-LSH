#include <iostream>
#include <random>
#include "../../headers/kmeansPP/kmeansPP.hpp"
#include "../../headers/distances.hpp"
#include "../../headers/common.hpp"

// Store the closest centroid index and distance for every image
vector<pair<int, unsigned int> > nearest_clusters;
// every index in vector stores its coordinates in an int* array
// in order to use it to manhattan distance
vector<int*> initial_centroids;
vector<int*> current_centroids;
vector<int*> previous_centroids;

int getRandomNumber(int number) {
	random_device generator;
	uniform_int_distribution<int> distribution (0, number - 1);
	return distribution(generator);
}

// MAY NEED CHANGES!!!!!!!! D^2
int* nextInitialCentroidCoords(uint32_t number_of_images) {
    // Adding the rest of the points according to the probability
	// unsigned int total_distance = 0;
	// for (int i = 0; i < number_of_images ; i++)
	// 	total_distance += nearest_clusters[i].second;

	// vector<unsigned int> v_i(number_of_images, 0);
	// for (int i = 0; i < number_of_images ; i++)
	// 	v_i[i] = (nearest_clusters[i].second / total_distance);
	
    // // Adding
	// for (int i = 1; i < number_of_images ; i++)
	// 	v_i[i] += v_i[i-1];

    // // random number between [0, 1]
	// int random_num = getRandomNumber(2);
	// for (int i = 0; i < v_i.size() ; i++)
	// 	if (random_num < v_i[i])
	// 		return i;

    // // take last v(i)
	// return v_i.size() - 1;


}

void getClosestCentroid (uint32_t index, vector<int*> centroids, uint64_t d) {
    int closest_cluster = -1;
    unsigned int min_distance = inf;
    for (unsigned int c = 0; c < centroids.size() ; c++) {
        unsigned int distance = manhattanDistance(centroids[c], cluster_images[index], d);
        if (distance < min_distance) {
            min_distance = distance;
            closest_cluster = c;
        }
    }
    if(closest_cluster == -1) {
        cerr << "Closest Cluster didn't update correctly" << endl;
        exit(ERROR);
    }
    nearest_clusters[index] = make_pair(closest_cluster, min_distance);
}

// calculate distance for every image for each centroid and
// select the smallest distance and save it in this cluster's centroid
// This function should have three different bodies
// the current body represent the Lloyd's, the other two will be the reverse LSH and reverse Cube
void updateNearClusters(vector<int*> centroids, uint32_t number_of_images, uint64_t d) {
    for (uint32_t i = 0; i < number_of_images; i++) {
        getClosestCentroid(i, centroids, d);        
    }
}

// k-medians, calculate the median in order to get next 
// cluster's centroid coords
void updateCentroids(vector<int*> centroids, uint32_t number_of_images, uint64_t d) {
    vector<int> temp_array;
    vector<int *> new_centroids;

    temp_array.resize(d);
    new_centroids.resize(centroids.size());

    for (unsigned int i=0; i<new_centroids.size(); i++) {
        new_centroids[i] = new int [d];
    }

    for (int c = 0; c < centroids.size(); c++) {
        // for loop for every image in the cluster c
        // call function that returns a vector with all the images in a given cluster, by centroid index
        for (){

            // make a for loop for every dimension of the d
            for (int i = 0; i < d; i++) {
                // calculate median value of all cluster_images in this cluster
                temp_array[i] = ;
            }
            // calculate the median of this temp array and store it in new_centroids[c][i]
            // in new_centroids[c] place the new coords

            temp_array.clear();
        }
    }
    // NOT TESTED
    // for (uint32_t i = 0; i < number_of_images ; i++) {
    //     size_of_cluster[nearest_clusters[i].first]++;
    //     for(int j=0 ; j < d ; j++)
    //         new_centroids[nearest_clusters[i].first][j] += input_data[i][j];
    // }
    // for (int i = 0; i < centroids.size() ; ++i)
    //     if(freq[i])
    //         for (int j = 0; j < centroids[i].size() ; ++j)
    //             new_centroids[i][j] *= (1.0/(double)freq[i]);
    // cur_centroids_ = new_centroids;

}

bool equalCentroids (uint64_t d) {
    unsigned int total_distance = 0;
    for (unsigned int i = 0; i < current_centroids.size(); i++) {
        total_distance += manhattanDistance(cluster_images[current_centroids[i]], cluster_images[previous_centroids[i]], d);
    }
    return (total_distance < SMALL_E);
}

vector<vector<int> > kmeansPP (int K, uint32_t number_of_images, uint64_t d) {
    // this is a vector of all centroids
    // for each centroid store a vector of images assigned in this cluster
    vector<vector<int> > clusters(K);
    // Get a random centroid
    int* first_centroid = new int [d];
    for (int i = 0; i < d;i++){
        // it will give random numbers for every dimension of the first centroid
        // max number will be 255 and min 0
        first_centroid[i] = getRandomNumber(256);
    }

    initial_centroids.push_back(first_centroid);
    // it will have one position for each image
    nearest_clusters.resize(number_of_images);

    // first centroid was randomly selected already
    // continue with Classic method (Lloyd's)
    for (int i = 1; i < K; i++) {
        // 
        updateNearClusters(initial_centroids, number_of_images, d);
        initial_centroids.push_back(nextInitialCentroidCoords(number_of_images));
    }

    current_centroids = initial_centroids;
    do {
        previous_centroids = current_centroids;
        // 
        updateNearClusters(current_centroids, number_of_images, d);
        updateCentroids(current_centroids, number_of_images, d);

    } while (!equalCentroids(d));

    // finally 
    for (uint32_t i = 0; i < number_of_images;i++)
        clusters[nearest_clusters[i].first].push_back(i);
    return clusters;
}