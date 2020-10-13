#include <cmath>
#include <iostream>
#include <random>
#include "../headers/manhattan-hashing.hpp"
#include "../headers/modulo.hpp"
using namespace std;

float* calculateURDComponents(uint64_t d){
	float* s_i = new float[d];
	float random;
	random_device generator;
	uniform_real_distribution<float> distribution (0.0, (float) w);

	for(uint64_t i=0; i<d; i++){ 	/* Each hash function has its own si */
		random = distribution(generator); /* Generate a new double number */
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
		// do the subtraction of x_i and s_i
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
	unsigned long long int ma = 0;
	int tempai = 0, temphx = 0;

	for (uint64_t i = 0; i < d; i++) {
		// m^x%M
		// calculate first component of current h(x)
		ma = exponentiationModulo(m, d-(i+1), M);
		// There is no reason to calculate a_i[i]ModM since M is way bigger than a_i[i]
		// So this operation will always give a_i[i] as a result
		tempai = customModulo(a_i[i], M);
		temphx = customModulo(ma*tempai, M);
		hx += customModulo(temphx, M);
		// cout << "mModM " << ma << " aiModM " << tempai<<" hx_iModM "<<temphx<<" temphxModM "<<hx<<endl;
	}
	hx = customModulo(hx, M);
	cout << "final hx is: " << hx << endl;
	return hx;
}