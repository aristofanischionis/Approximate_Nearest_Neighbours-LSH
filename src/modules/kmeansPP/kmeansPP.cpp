#include <iostream>
#include <random>
#include "../../headers/kmeansPP/kmeansPP.hpp"
#include "../../headers/distances.hpp"
#include "../../headers/common.hpp"

vector<pair<int, unsigned int> > nearest_clusters;
// include the coords of each centroid, while storing them
vector<int> initial_centroids;
vector<int> current_centroids;
vector<int> previous_centroids;

int getRandomNumber(int number) {
	random_device generator;
	uniform_int_distribution<int> distribution (0, number);
	return distribution(generator);
}

// TODO: Check again
int nextInitialCentroidIndex(uint32_t number_of_images) {
    //	Adding the rest of the points according to the probability
	unsigned int total_distance = 0;
	for (int i = 0; i < number_of_images ; i++)
		total_distance += nearest_clusters[i].second;

	vector<unsigned int> v_i(number_of_images, 0);
	for (int i = 0; i < number_of_images ; i++)
		v_i[i] = (nearest_clusters[i].second / total_distance);
	
    // Adding
	for (int i = 1; i < number_of_images ; i++)
		v_i[i] += v_i[i-1];

    // random number between [0, 1]
	int random_num = getRandomNumber(2);
	for (int i = 0; i < v_i.size() ; i++)
		if (random_num < v_i[i])
			return i;

    // take last v(i)
	return v_i.size() - 1;
}

// TODO: CHECK AGAIN
void getClosestCentroid (uint32_t index, vector<int> centroids, uint64_t d) {
    int closest_cluster = -1;
    unsigned int min_distance = inf;
    for (unsigned int c = 0; c < centroids.size() ; c++) {
        unsigned int distance = manhattanDistance(cluster_images[centroids[c]], cluster_images[index], d);
        if (distance < min_distance) {
            min_distance = distance;
            closest_cluster = c;
        }
    }
    if(closest_cluster == -1) {
        cerr << "Closest Cluster didn't update correctly" << endl;
        exit(ERROR);
    }
    nearest_clusters.push_back(make_pair(closest_cluster, min_distance));
}

void updateNearClusters(vector<int> centroids, uint32_t number_of_images, uint64_t d) {
    for (uint32_t i = 0; i < number_of_images; i++) {
        getClosestCentroid(i, centroids, d);        
    }
}

void updateCentroids(vector<int> centroids) {

}

bool equalCentroids (uint64_t d) {
    unsigned int total_distance = 0;
    for (unsigned int i = 0; i < current_centroids.size(); i++) {
        total_distance += manhattanDistance(cluster_images[current_centroids[i]], cluster_images[previous_centroids[i]], d);
    }
    return (total_distance < SMALL_E);
}

void kmeansPP (int K, int number_of_images, uint64_t d) {
    vector<int> clusters(K);
    // Get a random centroid
    int first_centroid = getRandomNumber(number_of_images);

    initial_centroids.push_back(first_centroid);
    
    // first centroid was randomly selected already
    for (int i = 1; i < K; i++){
        updateNearClusters(initial_centroids, number_of_images, d);
        initial_centroids.push_back(nextInitialCentroidIndex(number_of_images));
    }

    current_centroids = initial_centroids;
    // continue with Classic method (Lloyd's)
    do {
        previous_centroids = current_centroids;
        updateNearClusters(current_centroids, number_of_images, d);
        updateCentroids(current_centroids);

    } while (!equalCentroids(d));

    for (int i = 0; i < ;i++) {
        clusters[nearest_clusters]
    }
}