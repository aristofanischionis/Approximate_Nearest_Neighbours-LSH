#include <iostream>
#include "../../headers/kmeansPP/kmeansPP.hpp"
#include "../../headers/distances.hpp"
#include "../../headers/common.hpp"

// vector<pair<int*, vector<int> > > clusters(K);
unsigned int averageDistanceOfImageInCluster(int image, vector<pair<int*, vector<int> > > clusters, int c, u_int64_t d) {
    unsigned int total_dist = 0;
    // for all images in this cluster
    // except yourself
    for (int i = 0; i < clusters[c].second.size(); i++){
        if (clusters[c].second[i] == image) {
            // it's myself so continue
            continue;
        }
        // cluster_images[image]: is the current image who we check its distances
        // clusters[c].second[i]: is the index of the next image to be checked
        // cluster_images[clusters[c].second[i]]: are the coords of the above mentined image
        total_dist += manhattanDistance(cluster_images[image], cluster_images[clusters[c].second[i]], d);
    }

    // the loops above where (clusters[c].second.size() - 1), because it didn't run for it self
    return total_dist / (clusters[c].second.size() - 1);
}

// take a centroid and measure distance with all other centroids and return the coords of the closest one
int findSecondClosestCentroid (int* centroidCoords, vector<pair<int*, vector<int> > > clusters, u_int64_t d) {
    unsigned int min_distance = inf;
    int res_centroid = -1;
    int dist = 0;
    for (int c = 0; c < clusters.size(); c++) {
        dist = manhattanDistance(centroidCoords, clusters[c].first, d);
        if(dist < min_distance) {
            min_distance = dist;
            res_centroid = c;
        }
    }
    return res_centroid;
}

int calculateS_I (unsigned int a_i, unsigned int b_i) {
    return (b_i - a_i)/(a_i > b_i ? a_i : b_i);
}

void silhouette(vector<pair<int*, vector<int> > > clusters, u_int64_t d) {
    unsigned int a_i = 0, b_i = 0;
    int tmp_s_i;
    // store the average s_i of each cluster c in one spot in this vector
    int final_s_i = 0;
    // s_i.resize(clusters.size());
    
    for (int c = 0; c < clusters.size(); c++) {
        // for each image in this centroid "c" calculate the s(i)
        tmp_s_i = 0;
        for (int img = 0; img < clusters[c].second.size(); img++) {
            // calculate a_i component for this specific image
            a_i = averageDistanceOfImageInCluster(clusters[c].second[img], clusters, c, d);
            // calculate b_i component for this specific image
            b_i = averageDistanceOfImageInCluster(clusters[c].second[img], clusters, findSecondClosestCentroid(clusters[c].first, clusters, d), d);
            // add to the counter for the s_i calculation
            tmp_s_i += calculateS_I(a_i, b_i);
        }
        // calculate the average s(i) of all images in this cluster (centroid)
        // now in tmp_s_i I have the sum of all s_i for this cluster
        tmp_s_i /= clusters[c].second.size();
        final_s_i += tmp_s_i;
    }

    final_s_i /= clusters.size();
    // I got the final value for the s_i
    // now evaluate if its -1, 0 or 1
    switch (final_s_i) {
        case -1: {
            cout << "Silhouette result was -1, K should be changed" << endl;
            break;
        }
        case 0: {
            cout << "Silhouette result was 0, could be better" << endl;
            break;
        }
        case 1: {
            cout << "Silhouette result was 1, everything good" << endl;
            break;
        }
        default: {
            cout << "Silhouette result was " << final_s_i << " , something is going wrong" << endl;
            break;
        }
    }
}