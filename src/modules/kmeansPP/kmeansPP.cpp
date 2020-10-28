#include <iostream>
#include <random>
#include <algorithm>
#include "../../headers/kmeansPP/kmeansPP.hpp"
#include "../../headers/distances.hpp"
#include "../../headers/common.hpp"

#include <vector>
using namespace std;

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

double getRealRandomNumber(double number) {
    random_device generator;
    uniform_real_distribution<double> distribution (0.0, number);
    return distribution(generator);
}

vector<int> getImagesInCluster(int centroid_idx) {
    vector<int> images_in_cluster;
    for (unsigned int i = 0; i < nearest_clusters.size(); i++) {
        if(nearest_clusters[i].first == centroid_idx) {
            images_in_cluster.push_back(i);
        }
    }
    return images_in_cluster;
}

int nextInitialCentroidCoords(uint32_t number_of_images) {
    // Adding the rest of the points according to the probability
	unsigned int total_distance = 0;
    for (uint32_t i = 0; i < number_of_images; i++) {
        total_distance += nearest_clusters[i].second;
    }

	vector<double> v_i(number_of_images, 0);
	for (unsigned int i = 0; i < number_of_images ; i++) {
        v_i.insert(v_i.begin()+i, static_cast<double>(nearest_clusters[i].second) / static_cast<double>(total_distance));
    }
	
    // Adding
	for (uint32_t i = 1; i < number_of_images ; i++) {
        v_i.insert(v_i.begin()+i, v_i[i] + v_i[i-1]);
    }

    double rand_num = getRealRandomNumber(1.0);
	for (uint32_t i = 0; i < number_of_images ; i++) {
        if (rand_num < v_i[i]) {
            return i;
        }
    }
    return number_of_images - 1;
}

void getClosestCentroid(uint32_t index, vector<int*> centroids, uint64_t d) {
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
void updateCentroids(vector<int*> &centroids, uint32_t number_of_images, uint64_t d) {
    vector<int> temp_array;
    vector<int *> new_centroids;
    vector<int> images_in_cluster;

    new_centroids.resize(centroids.size());

    for (unsigned int i=0; i< new_centroids.size(); i++) {
        new_centroids[i] = new int [d];
    }
    for (unsigned int c = 0; c < centroids.size(); c++) {
        // for loop for every image in the cluster c
        // call function that returns a vector with all the images in a given cluster, by centroid index
        images_in_cluster = getImagesInCluster(c);
        // temp_array.resize(images_in_cluster.size());
        // make a for loop for every dimension of the d
        for (uint64_t j = 0; j < d; j++) {
            temp_array.resize(images_in_cluster.size());
            for (unsigned int img = 0; img < images_in_cluster.size(); img++) {
                int p = cluster_images[images_in_cluster[img]][j];
                temp_array[img] = p;
            }
            // find median
            sort(temp_array.begin(), temp_array.end());
            new_centroids[c][j] = temp_array[temp_array.size()/2];
            temp_array.clear();
        }
    }
    // we have new_centroids array ready, with updated values
    centroids = new_centroids;
    // copy(centroids.begin(), centroids.end(), back_inserter(new_centroids));
    // centroids.assign(new_centroids.begin(), new_centroids.end());

    temp_array.clear();
    images_in_cluster.clear();
    new_centroids.clear();
}

bool equalCentroids(uint64_t d, int loops) {
    unsigned int total_distance = 0;
    if (loops > MAX_LOOPS) return true;
    for (unsigned int i = 0; i < current_centroids.size(); i++) {
        total_distance += manhattanDistance(current_centroids[i], previous_centroids[i], d);
    }
    return (total_distance < SMALL_E);
}

vector<pair<int*, vector<int> > > kmeansPP(int K, uint32_t number_of_images, uint64_t d) {
    // this is a vector of all centroids
    // for each centroid store a vector of images assigned in this cluster
    vector<vector<int> > temp(K);
    vector<pair<int*, vector<int> > > clusters(K);
    int loops = 0;
    // Get a random centroid
    int* first_centroid = new int [d];
    
    first_centroid = cluster_images[getRandomNumber(number_of_images)];
    initial_centroids.push_back(first_centroid);
    // it will have one position for each image
    nearest_clusters.resize(number_of_images);

    // Initialize the K centroids
    for (int i = 1; i < K; i++) {
        updateNearClusters(initial_centroids, number_of_images, d);
        initial_centroids.push_back(cluster_images[nextInitialCentroidCoords(number_of_images)]);
    }

    current_centroids = initial_centroids;
    do {
        previous_centroids = current_centroids;
        updateNearClusters(current_centroids, number_of_images, d);
        updateCentroids(current_centroids, number_of_images, d);
        loops++;
    } while (!equalCentroids(d, loops));

    // finally make the data for silhouette
    for (uint32_t i = 0; i < number_of_images;i++)
        temp[nearest_clusters[i].first].push_back(i);
    for (int i = 0; i < K;i++)
        clusters[i] = make_pair(current_centroids[i], temp[i]);
    return clusters;
}