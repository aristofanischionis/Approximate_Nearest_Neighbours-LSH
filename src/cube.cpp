#include "headers/cube/cube.hpp"
#include "headers/cube/projection.hpp"
#include "headers/cube/handle-cube-input.hpp"
#include <fstream>
using namespace std;

// I use these arrays from this header "headers/handle-input.hpp"
//  I think it's okay to do so, because I have to include it anyway to use other functions from there
unsigned char** all_cube_images = NULL;
unsigned char** query_cube_images = NULL;
unsigned int w;

int main(int argc, char **argv) {
    uint32_t number_of_images = 0;
    int k = SMALL_CUBE_K;
	int n = SMALL_N;
	int points_M = POINTS_M;
	int probes = PROBES;
	unsigned int r = SMALL_R;
    uint64_t d = 0;
    w = 400;
    string output_file, query_file;
    ofstream o_file;

    handleCubeInput(argc, argv, &number_of_images, &d, &k, &points_M, &probes, &n, &r, &output_file, &query_file);
    // TODO: FREE UP MEMORY
}