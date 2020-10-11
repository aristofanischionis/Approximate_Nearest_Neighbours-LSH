#include "../headers/manhattan-hashing.hpp"

using namespace std;

float* calculateURDComponents(int d){

	float* s = new float[d];
	int w = 10;

	float random;

	random_device generator;
	uniform_real_distribution<float> distribution (0.0, (float) w);

	for(int i=0;i<d;i++){ 	/* Each hash function has its own s */

		random = distribution(generator); /* Generate a new double number */

		s[i] = random;
	}
	return s;
}