#include <random>
#include "../../headers/kmeansPP/kmeansPP.hpp"
#include "../../headers/distances.hpp"

vector<pair<int, unsigned int> > nearest_clusters;
vector<int> initial_centroids;
vector<int> current_centroids;
vector<int> previous_centroid;

int getRandomCentroid(int number_of_images) {
	random_device generator;
	uniform_real_distribution<int> distribution (0, number_of_images);
	return distribution(generator);
}

// TODO
int nextInitialCentroidIndex() {
    int index = 0;

    return index;
}

// use initial_centroids
void updateNearClusters() {

}

bool equalCentroids (uint64_t d) {
    unsigned int total_distance = 0;
    for (unsigned int i = 0; i < current_centroids.size(); i++) {
        total_distance += manhattanDistance(cluster_images[current_centroids[i]], cluster_images[previous_centroid[i]], d);
    }
    return (total_distance < SMALL_E);
}

void kmeansPP (int K, int number_of_images, uint64_t d) {
    vector<int> clusters(K);
    int first_centroid = getRandomCentroid(number_of_images);

    initial_centroids.push_back(first_centroid);
    
    // first centroid was randomly selected already
    for (int i = 1; i < K;i++){
        updateNearClusters();
        initial_centroids.push_back(nextInitialCentroidIndex());
    }

    current_centroids = initial_centroids;
    // TODO
    do {

    } while (!equalCentroids(d));
}