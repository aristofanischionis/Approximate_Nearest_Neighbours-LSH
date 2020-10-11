#include <math.h>
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
	int* a_i = new int[d];
	float* x_i = new float[d];
	for (int i = 0; i < d; i++) {
		x_i[i] = static_cast<float>(x_i_array[i]);
	}
	// this function does x_i - s_i for all the items in the two arrays
	transform(x_i, x_i + d, s_i, a_i, minus<float>());
	for (int i= 0; i < d; i++)
		cout << "a_i: " << abs(a_i[i]) << endl;
	return a_i;
}