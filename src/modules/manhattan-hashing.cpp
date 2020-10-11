#include <math.h>
#include <valarray>
#include "../headers/manhattan-hashing.hpp"
using namespace std;

float* calculateURDComponents(uint64_t d){
	float* s = new float[d];
	float random;
	random_device generator;
	uniform_real_distribution<float> distribution (0.0, (float) w);

	for(int i=0;i<d;i++){ 	/* Each hash function has its own s */
		random = distribution(generator); /* Generate a new double number */
		s[i] = random;
	}
	return s;
}

int* calculateA_IComponents(unsigned char* x_i_array, float* s_i, uint64_t d) {
	// with this function we will calcuate the a_i components
	// for an image
	float sub, div;
	int *a_i = new int[d];
	float* x_i = new float[d];

	for (int i = 0; i < d; i++) {
		// transform the unsigned char* to float
		x_i[i] = static_cast<float>(x_i_array[i]);
		// do the subtraction of x_i and s_i
		sub = x_i[i] - s_i[i];
		// divide the subtraction with the w, which is globally accessible
		div = sub / w;
		// find the floor of the division
		a_i[i] = static_cast<int>(floor(static_cast<double>(div)));
	}
	return a_i;
}