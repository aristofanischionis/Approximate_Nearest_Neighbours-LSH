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
	uniform_int_distribution<int> distribution (0, number);
	return distribution(generator);
}

// MAY NEED CHANGES!!!!!!!! D^2
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
    nearest_clusters[index] = make_pair(closest_cluster, min_distance);
}

void updateNearClusters(vector<int> centroids, uint32_t number_of_images, uint64_t d) {
    for (uint32_t i = 0; i < number_of_images; i++) {
        getClosestCentroid(i, centroids, d);        
    }
}

void updateCentroids(vector<int> centroids) {
    vector<int>freq(centroids_.size(),0);
    vector<datapoint>new_centroids(centroids_.size(),vector<double>(centroids_[0].size(),0));
    for (int i = 0; i < input_data.size() ; ++i) {
        ++freq[nearest_cluster_idx[i]];
        for(int j=0 ; j< input_data[i].size() ; ++j)
            new_centroids[nearest_cluster_idx[i]][j] += input_data[i][j];
    }

    for (int i = 0; i < centroids_.size() ; ++i)
        if(freq[i])
            for (int j = 0; j < centroids_[i].size() ; ++j)
                new_centroids[i][j] *= (1.0/(double)freq[i]);
    cur_centroids_ = new_centroids;
}

bool equalCentroids (uint64_t d) {
    unsigned int total_distance = 0;
    for (unsigned int i = 0; i < current_centroids.size(); i++) {
        total_distance += manhattanDistance(cluster_images[current_centroids[i]], cluster_images[previous_centroids[i]], d);
    }
    return (total_distance < SMALL_E);
}

vector<vector<int> > kmeansPP (int K, int number_of_images, uint64_t d) {
    vector<vector<int> > clusters(K);
    // Get a random centroid
    int first_centroid = getRandomNumber(number_of_images);

    initial_centroids.push_back(first_centroid);
    
    nearest_clusters.resize(number_of_images);

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

    for (uint32_t i = 0; i < number_of_images;i++)
        clusters[nearest_clusters[i].first].push_back(i);
    return clusters;
}