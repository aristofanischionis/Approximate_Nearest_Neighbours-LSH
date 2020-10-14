#include <cmath>
#include <iostream>
#include <random>
#include "../headers/manhattan-hashing.hpp"
#include "../headers/modulo.hpp"
using namespace std;

float* calculateURDComponents(uint64_t d) {
	float* s_i = new float[d];
	float random;
	random_device generator;
	uniform_real_distribution<float> distribution (0.0, (float) w);

	// Each hash function has its own si
	for(uint64_t i=0; i<d; i++) {
		// Generate a new double number
		random = distribution(generator);
		s_i[i] = random;
	}
	return s_i;
}

int* calculateA_IComponents(unsigned char* x_i_array, float* s_i, uint64_t d) {
	// with this function we will calcuate the a_i components
	// for an image
	float sub, div;
	int *a_i = new int[d];
	float x_i[d];

	for (uint64_t i=0; i<d; i++) {
		// transform the unsigned char* to float
		x_i[i] = static_cast<float>(x_i_array[i]);
		// ADD w, to all x_i, this will move all of the x_i s away from the start of axis
		// Will remove the problem of having negative numbers in the a_i components!
		sub = x_i[i] + w - s_i[i];
		// divide the subtraction with the w, which is globally accessible
		div = sub / w;
		// find the floor of the division
		a_i[i] = static_cast<int>(floor(static_cast<double>(div)));
	}
	return a_i;
}

unsigned long calculateH_XComponent(int* a_i, uint64_t d) {
	unsigned long int hx = 0;
	unsigned long long int mExp = 0;
	int tempai = 0, temphx = 0;

	// calculate each component of current h(x)
	for (uint64_t i = 0; i < d; i++) {
		// m^x%M
		mExp = exponentiationModulo(m, d-(i+1), M);
		tempai = customModulo(a_i[i], M);
		temphx = customModulo(mExp*tempai, M);
		hx += customModulo(temphx, M);
	}
	
	hx = customModulo(hx, M);
	return hx;
}