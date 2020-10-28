#include <stdint.h>
#include <vector>
// random value for now find the best
// TODO
#define SMALL_E 100 
#define MAX_LOOPS 9

using namespace std;

extern vector<pair<int, unsigned int> > nearest_clusters;
// in the centroid vectors, store the indexes, 
// which correspond to each image
// To access the array with the dimensions, use cluster_images[i]

extern vector<int*> initial_centroids;
extern vector<int*> current_centroids;
extern vector<int*> previous_centroid;
// in cluster images, I save number_of_images images (is a d-dimensional array)
extern int** cluster_images;

void readClusterFile(const string&, uint32_t*, uint64_t*);
void kmeansPP (int, uint32_t, uint64_t);